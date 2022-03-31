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
	//모르빗 주변 범위 200 안에 있는 액터 탐지, EnemyDetect 트레이스 채널 사용
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Morbit);
	bool bResult = World->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
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
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1차 탐지
				if(Morbit->GetTestMode())
					STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // 무시할 액터 유형?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery는 콜리전 프리셋의 트레이스 유형에서 1부터 순차적으로 부여됨
				if (Morbit->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Morbit->GetActorLocation(), // SphereTrace 시작 위치
						Player->GetActorLocation(), // SphereTrace 종료 위치
						5.0f,
						ETraceTypeQuery::TraceTypeQuery4,
						false,
						ActorsToIgnore,
						EDrawDebugTrace::ForDuration, // 마지막 인자값으로 시간 조절 가능
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
					//2차 탐지
					if (Morbit->GetTestMode())
						STARRYLOG(Warning, TEXT("Detect Player in SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Morbit->GetActorLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit의 정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
					float Radian = FVector::DotProduct(Morbit->GetActorForwardVector(), TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					//플레이어 위치에 따른 탐지 조정 필요, 발끝과 머리의 Z값 정보
					if (TargetAngle <= (Morbit->GetViewAngle() * 0.5f))
					{
						//3차 탐지
						if (Morbit->GetTestMode())
							STARRYLOG(Warning, TEXT("Detect Player in MorbitFOV"));
						//몬스터 대기상태 지정

						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsFindKey, true);

						//몬스터 탐색
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