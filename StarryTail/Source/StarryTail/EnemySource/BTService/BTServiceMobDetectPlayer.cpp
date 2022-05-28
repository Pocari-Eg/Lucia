// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceMobDetectPlayer.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTServiceMobDetectPlayer::UBTServiceMobDetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
	Interval = 1.0f;
}
void UBTServiceMobDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	FVector Box = FVector(Monster->GetViewRange(), Monster->GetViewRange(), Monster->GetViewHeight());
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = World->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeBox(Box),
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
				if(Monster->GetTestMode())
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
						STARRYLOG(Warning, TEXT("Detect Player in SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (Monster->GetViewAngle() * 0.5f))
					{
						//3�� Ž��
						if (Monster->GetTestMode())
							STARRYLOG(Warning, TEXT("Detect Player in MorbitFOV"));
						//���� ������ ����

						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, true);

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
		FVector RightDir = Monster->AngleToDir(Monster->GetActorRotation().Euler().Z + Monster->GetViewAngle() * 0.5f) * Monster->GetViewRange();
		FVector LeftDir = Monster->AngleToDir(Monster->GetActorRotation().Euler().Z - Monster->GetViewAngle() * 0.5f) * Monster->GetViewRange();
		FVector LookDir = Monster->GetActorForwardVector() * Monster->GetViewRange();
		
		DrawDebugLine(World, CenterTop, CenterBottom, FColor::Red, false, 0.2f);

		DrawDebugLine(World, CenterBottom, CenterBottom + RightDir, FColor::Blue, false, 0.2f);
		DrawDebugLine(World, CenterBottom, CenterBottom + LeftDir, FColor::Blue, false, 0.2f);

		DrawDebugLine(World, CenterTop, CenterTop + RightDir, FColor::Blue, false, 0.2f);
		DrawDebugLine(World, CenterTop, CenterTop + LeftDir, FColor::Blue, false, 0.2f);

		DrawDebugLine(World, CenterBottom + RightDir, CenterTop + RightDir, FColor::Blue, false, 0.2f);
		DrawDebugLine(World, CenterBottom + LeftDir, CenterTop + LeftDir, FColor::Blue, false, 0.2f);

		DrawDebugLine(World, CenterBottom + LeftDir, CenterBottom + LookDir, FColor::Blue, false, 0.2f);
		DrawDebugLine(World, CenterBottom + LookDir, CenterBottom + RightDir, FColor::Blue, false, 0.2f);

		DrawDebugLine(World, CenterTop + LeftDir, CenterTop + LookDir, FColor::Blue, false, 0.2f);
		DrawDebugLine(World, CenterTop + LookDir, CenterTop + RightDir, FColor::Blue, false, 0.2f);
	}
}