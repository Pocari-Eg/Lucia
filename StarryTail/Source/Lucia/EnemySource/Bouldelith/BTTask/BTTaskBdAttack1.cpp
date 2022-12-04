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
		//�𸣺� �ֺ� ���� 200 �ȿ� �ִ� ���� Ž��, EnemyDetect Ʈ���̽� ä�� ���
		TArray<FOverlapResult> OverlapResults;
		FCollisionQueryParams CollisionQueryParam(NAME_None, false, Monster);
		bool bResult = Monster->GetWorld()->OverlapMultiByChannel( // ������ Collision FCollisionShape�� �浹�� ���� ���� 
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
				//�÷��̾� Ŭ���� ������ �������� PlayerController�� �����ϰ� �ִ°� Ȯ��
				AIreneCharacter* Player = Cast<AIreneCharacter>(OverlapResult.GetActor());
				if (Player && Player->GetController()->IsPlayerController())
				{
					//1�� Ž��
					//if (Monster->GetTestMode())
						//STARRYLOG(Warning, TEXT("Detect Player in DetectSphere"));

					TArray<FHitResult> Hits;
					TArray<AActor*> ActorsToIgnore; // ������ ���� ����?
					bool bTraceResult;

					// https://blog.daum.net/peace-day/22
					// TraceTypeQuery�� �ݸ��� �������� Ʈ���̽� �������� 1���� ���������� �ο���
					if (Monster->GetTestMode())
					{
						bTraceResult = UKismetSystemLibrary::SphereTraceMulti(
							Monster->GetWorld(),
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
						//2�� Ž��
						//if (Monster->GetTestMode())
							//STARRYLOG(Warning, TEXT("Attack in Player SphereTrace"));

						FVector TargetDir = Player->GetActorLocation() - Monster->GetLocation();
						TargetDir = TargetDir.GetSafeNormal();

						float Radian = FVector::DotProduct(Monster->GetActorForwardVector(), TargetDir);
						//���� ������� Cos{^-1}(A dot B / |A||B|)�̱� ������ ��ũ�ڻ��� �Լ��� ������ְ� Degree�� ��ȯ���ش�.
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