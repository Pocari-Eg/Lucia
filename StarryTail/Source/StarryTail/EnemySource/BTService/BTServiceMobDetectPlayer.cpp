// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiceMobDetectPlayer.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"

#include "Kismet/KismetSystemLibrary.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTServiceMobDetectPlayer::UBTServiceMobDetectPlayer()
{
	NodeName = TEXT("DetectPlayer");
	Interval = 0.1f;
}
void UBTServiceMobDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return;

	UWorld* World = Monster->GetWorld();
	FVector Center = Monster->GetLocation() + (-Monster->GetActorForwardVector() * Monster->GetCapsuleComponent()->GetScaledCapsuleRadius());


	FVector Box = FVector(Monster->GetViewRange(), Monster->GetViewRange(), Monster->GetViewHeight());
	//모르빗 주변 범위 200 안에 있는 액터 탐지, EnemyDetect 트레이스 채널 사용
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
	bool bResult = World->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
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
			//플레이어 클래스 정보를 가져오고 PlayerController를 소유하고 있는가 확인
			AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
			if (Player && Player->GetController()->IsPlayerController())
			{
				//1차 탐지
				if(Monster->GetTestMode())
					STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

				TArray<FHitResult> Hits;
				TArray<AActor*> ActorsToIgnore; // 무시할 액터 유형?
				bool bTraceResult;

				// https://blog.daum.net/peace-day/22
				// TraceTypeQuery는 콜리전 프리셋의 트레이스 유형에서 1부터 순차적으로 부여됨
				if (Monster->GetTestMode())
				{
					bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
						World,
						Monster->GetLocation(), // SphereTrace 시작 위치
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
					//2차 탐지
					if (Monster->GetTestMode())
						STARRYLOG(Warning, TEXT("Detect Player in SphereTrace"));

					FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
					TargetDir = TargetDir.GetSafeNormal();

					//Morbit의 정면으로 향하는 벡터와 플레이어로 향하는 벡터의 내적을 통해 각도를 구할 수 있다. 결과값은 Radian
					float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
					//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
					float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

					if (TargetAngle <= (360.0f * 0.5f))
					{
						//3차 탐지
						if (Monster->GetTestMode())
							STARRYLOG(Warning, TEXT("Detect Player in MorbitFOV"));
						//몬스터 대기상태 지정
						Monster->GetAIController()->SetFind();
						return;
					}
					else {
						OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
					}
					
				}
				else {
					OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);

				}
				
			}
			else {
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);

			}
		}
	}
	else {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
	}

	if (Monster->GetTestMode())
	{
		FTransform BottomLine = Monster->GetTransform();
		BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, 220.0f));
		FTransform TopLine = BottomLine;
		TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, 200.0f));

		FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
		FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();


	   Monster->GetAIController()->DrawRadial(World, BottomDebugMatrix, Monster->GetViewRange(), 360.0f, FColor::Blue,10, 0.1f,false,0,2);
	   Monster->GetAIController()->DrawRadial(World, TopDebugMatrix, Monster->GetViewRange(), 360.0f, FColor::Blue, 10, 0.1f, false, 0, 2);
	}

}


