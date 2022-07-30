// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceMobAttackInPlayer.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BTServiceMobDetectPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
UBTServiceMobAttackInPlayer::UBTServiceMobAttackInPlayer()
{
	NodeName = TEXT("AttackInPlayer");
	Interval = 1.0f;
}
void UBTServiceMobAttackInPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return;

	UWorld* World = Monster->GetWorld();
	FVector Center = Monster->GetLocation() + (-Monster->GetActorForwardVector() * Monster->GetCapsuleComponent()->GetScaledCapsuleRadius());

	FVector CenterBottom = Center;
	CenterBottom.Z -= 85.0f;

	FVector CenterTop = CenterBottom;
	CenterTop.Z += 150.0f;

	FVector Box = FVector(Monster->GetAtkRange(), Monster->GetAtkRange(), Monster->GetAtkHeight());
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = World->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeCapsule(Box),
		CollisionQueryParam
	);






	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1�� Ž��
				if (Monster->GetTestMode())
					STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Monster->GetLocation(), // SphereTrace ���� ��ġ
						Player->GetActorLocation(), // SphereTrace ���� ��ġ
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // ������ ���ڰ����� �ð� ���� ����
						Hits,
						true,
						FLinearColor::Red,
						FLinearColor::Green,
						1.0f
					);
				}
				else
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Monster->GetLocation(),
						Player->GetActorLocation(),
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::None,
						Hits,
						true
					);
				}

				for (int i = 0; i < Hits.Num(); i++)
				{
					Player = Cast<AIreneCharacter>(Hits[i].GetActor());
					if (Player != nullptr)
					{
						break;
					}
				}

				if (bTraceResult && !(nullptr == Player))
				{
					//2�� Ž��
					if (Monster->GetTestMode())
						STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetAtkAngle() * 0.5f))
					{
						//3�� Ž��
						if (Monster->GetTestMode())
							STARRYLOG(Warning, TEXT("Attack in Player MorbitFOV"));
						//���� ������ ����
						Monster->GetAIController()->SetAttackAble(true);
						//���� Ž��
						TArray<FOverlapResult> AnotherMonsterList = Monster->DetectMonster(Monster->GetDetectMonsterRange());
						if (AnotherMonsterList.Num() != 0)
						{
							for (auto const& AnotherMonster : AnotherMonsterList)
							{
								auto Mob = Cast<AMonster>(AnotherMonster.GetActor());
								if (Mob == nullptr)
									continue;

								auto AnotherMonsterAIController = Cast<AMonsterAIController>(Mob->GetController());
								if (AnotherMonsterAIController == nullptr)
									continue;

								AnotherMonsterAIController->SetFind();
							}
						}

						return;
					}
				}
			}
		}
	}

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 220.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAtkHeight()));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

		STARRYLOG_S(Error);
		DrawRadial(World, BottomDebugMatrix, Monster->GetAtkRange(), Monster->GetAtkAngle(), FColor::Red, 10, 0.2f, false, 0, 2);
		DrawRadial(World, TopDebugMatrix, Monster->GetAtkRange(), Monster->GetAtkAngle(), FColor::Red, 10, 0.2f, false, 0, 2);
	}

}

