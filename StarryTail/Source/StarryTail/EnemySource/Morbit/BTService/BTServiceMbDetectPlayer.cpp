// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceMbDetectPlayer.h"
#include "../MbAIController.h"
#include "../../MonsterAIController.h"
#include "../Morbit.h"
#include "../../../IreneCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTServiceMbDetectPlayer::UBTServiceMbDetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
	Interval = 1.0f;
}
void UBTServiceMbDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Morbit = Cast<AMorbit>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Morbit)
		return;

	UWorld* World = Morbit->GetWorld();
	FVector Center = Morbit->GetActorLocation() + (-Morbit->GetActorForwardVector() * 50.0f);

	FVector CenterBottom = Center;
	CenterBottom.Z -= 85.0f;

	FVector CenterTop = CenterBottom;
	CenterTop.Z += 150.0f;

	FVector Box = FVector(Morbit->GetViewRange(), Morbit->GetViewRange(), 150.0f);
	//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Morbit);
	bool bResult = World->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeBox(Box),
		CollisionQueryParam
	);

	DrawDebugBox(World, Center, Box, FColor::Red, false, 0.2f);

	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1�� Ž��
				if(Morbit->GetTestMode())
					STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
				if (Morbit->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Morbit->GetActorLocation(), // SphereTrace ���� ��ġ
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
						Morbit->GetActorLocation(),
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
					if (Morbit->GetTestMode())
						STARRYLOG(Warning, TEXT("Detect Player in SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Morbit->GetActorLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit�� �������� ���ϴ� ���Ϳ� �÷��̾�� ���ϴ� ������ ������ ���� ������ ���� �� �ִ�. ������� Radian
					float Radian = FVector::DotProduct(Morbit->GetActorForwardVector(), TargetDir);
					//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					//�÷��̾� ��ġ�� ���� Ž�� ���� �ʿ�, �߳��� �Ӹ��� Z�� ����
					if (TargetAngle <= (Morbit->GetViewAngle() * 0.5f))
					{
						//3�� Ž��
						if (Morbit->GetTestMode())
							STARRYLOG(Warning, TEXT("Detect Player in MorbitFOV"));
						//���� ������ ����

						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsFindKey, true);

						//���� Ž��
						TArray<FOverlapResult> AnotherMonsterList = Morbit->DetectMonster();
						if (AnotherMonsterList.Num() != 0)
						{
							for (auto const& AnotherMonster : AnotherMonsterList)
							{
								auto Monster = Cast<AMonster>(AnotherMonster.GetActor());
								if (Monster == nullptr)
									continue;

								auto AnotherMonsterAIController = Cast<AMonsterAIController>(Monster->GetController());
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

	

	if (Morbit->GetTestMode())
	{
		FVector RightDir = AngleToDir(Morbit->GetActorRotation().Euler().Z + Morbit->GetViewAngle() * 0.5f) * Morbit->GetViewRange();
		FVector LeftDir = AngleToDir(Morbit->GetActorRotation().Euler().Z - Morbit->GetViewAngle() * 0.5f) * Morbit->GetViewRange();
		FVector LookDir = Morbit->GetActorForwardVector() * Morbit->GetViewRange();
		
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
FVector UBTServiceMbDetectPlayer::AngleToDir(float angle)
{
	float radian = FMath::DegreesToRadians(angle);
	FVector Dir = FVector(FMath::Cos(radian), FMath::Sin(radian), 0.f);

	return Dir;
}