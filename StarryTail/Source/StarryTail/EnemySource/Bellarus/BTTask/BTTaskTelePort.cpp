// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTelePort.h"
#include "../Bellarus.h"
#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../BTService/BTServiceAttackJudge.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskTelePort::UBTTaskTelePort()
{
	NodeName = TEXT("TelePortATTACK");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskTelePort::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	Bellarus->PlayTelePortAnim();
	Bellarus->GetAIController()->StopMovement();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellarus->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskTelePort::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);

		Cast<ABellarusAIController>(Monster->GetAIController())->AllAttackOff();
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		if (Cast<ABellarusAIController>(Monster->GetAIController())->GetSecondPhaseKey() == true) {
			SecondPhaseAction(Monster, OwnerComp);
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTaskTelePort::SecondPhaseAction(ABellarus* Monster, UBehaviorTreeComponent& OwnerComp)
{
	FVector Center = Monster->GetLocation();
	Center -= FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	bool FirstJudge = UBTServiceAttackJudge::AttackJudge(Monster, Center, Monster->GetFirstJugdeRadius(), FColor::Green);
	if (FirstJudge)
	{
		auto Ran = FMath::RandRange(1, 100);
		if (Ran <= 70)
		{
			Ran = FMath::RandRange(1, 100);

			if (Ran <= 50)
			{
			Cast<ABellarusAIController>(Monster->GetAIController())->SetWingRKey(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
			else
			{
				Cast<ABellarusAIController>(Monster->GetAIController())->SetWingLKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}

		}

	
	}
}
