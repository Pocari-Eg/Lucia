// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack1.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

#include"../BTService/BTServiceBdAttackTrace.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskBdAttack1::UBTTaskBdAttack1()
{
	NodeName = TEXT("Attack1");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Attack1();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bouldelith->Attack1End.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
	

		if (Monster->GetTestMode())
		{
			FTransform BottomLine = Monster->GetTransform();

			BottomLine.SetLocation(BottomLine.GetLocation() - FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));


			FTransform TopLine = BottomLine;
			TopLine.SetLocation(TopLine.GetLocation() + FVector(0.0f, 0.0f, Monster->GetAttack2Range().M_Atk_Height));
			FMatrix BottomDebugMatrix = BottomLine.ToMatrixNoScale();
			FMatrix TopDebugMatrix = TopLine.ToMatrixNoScale();

			Monster->GetAIController()->DrawRadial(Monster->GetWorld(), BottomDebugMatrix, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
			Monster->GetAIController()->DrawRadial(Monster->GetWorld(), TopDebugMatrix, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Angle, FColor::Red, 10, 0.1f, false, 0, 2);
		}

		FVector Box = FVector(Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Radius, Monster->GetAttack2Range().M_Atk_Height);
		//모르빗 주변 범위 200 안에 있는 액터 탐지, EnemyDetect 트레이스 채널 사용
		TArray<FOverlapResult> OverlapResults;
		FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
		bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // 지정된 Collision FCollisionShape와 충돌한 액터 감지 
			OverlapResults,
			Monster->GetActorLocation(),
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
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

					TArray<FHitResult> Hits;
					TArray<AActor*> ActorsToIgnore; // 무시할 액터 유형?
					bool bTraceResult;

					// https://blog.daum.net/peace-day/22
					// TraceTypeQuery는 콜리전 프리셋의 트레이스 유형에서 1부터 순차적으로 부여됨
					if (Monster->GetTestMode())
					{
						bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
							Monster->GetWorld(),
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
							Monster->GetWorld(),
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
						//if (Monster->GetTestMode())
							//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

						FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
						TargetDir = TargetDir.GetSafeNormal();

						float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
						//내적 결과값은 Cos{^-1}(A dot B / |A||B|)이기 때문에 아크코사인 함수를 사용해주고 Degree로 변환해준다.
						float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(Radian));

						if (TargetAngle <= (Monster->GetAttack2Range().M_Atk_Angle * 0.5f))
						{


							auto ran = FMath::RandRange(1, 100);
							if (ran <= 80)
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
								Monster->GetAIController()->OnAttack(2);
								FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
								return;
							}
							
						}
	

					}
	

				}

			}
		}




		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		Monster->GetAIController()->OffAttack(1);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}