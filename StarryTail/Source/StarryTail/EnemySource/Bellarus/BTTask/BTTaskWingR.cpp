// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskWingR.h"
#include "../Bellarus.h"
#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../BTService/BTServiceAttackJudge.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskWingR::UBTTaskWingR()
{
	NodeName = TEXT("WING_RATTACK");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskWingR::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	Bellarus->PlayWingRAnim();
	Bellarus->GetAIController()->StopMovement();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellarus->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskWingR::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		Cast<ABellarusAIController>(Monster->GetAIController())->AllAttackOff();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellarusAIController::CheckKey, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
		if (Cast<ABellarusAIController>(Monster->GetAIController())->GetSecondPhaseKey() == true) {
			SecondPhaseAction(Monster, OwnerComp);
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTTaskWingR::SecondPhaseAction(ABellarus* Monster, UBehaviorTreeComponent& OwnerComp)
{
	if (Cast<ABellarusAIController>(Monster->GetAIController())->GetSecondPhaseKey() == true) {
		FVector Center = Monster->GetLocation();
		Center -= FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
		bool FirstJudge = UBTServiceAttackJudge::AttackJudge(Monster, Center, Monster->GetFirstJugdeRadius(), FColor::Green);
		if (FirstJudge)
		{
			if (Cast<ABellarusAIController>(Monster->GetAIController())->GetIsShieldOn())
			{
			auto Ran = FMath::RandRange(1, 100);
			if (Ran <= 40)
			{
				Cast<ABellarusAIController>(Monster->GetAIController())->SetWingLKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}

			Ran = FMath::RandRange(1, 100);
			if (Ran <= 40)
			{
				Cast<ABellarusAIController>(Monster->GetAIController())->SetTailKey(true);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		  }
			else {

				auto Ran = FMath::RandRange(1, 100);
				if (Ran <= 60)
				{
					Cast<ABellarusAIController>(Monster->GetAIController())->SetWingLKey(true);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				}

				Ran = FMath::RandRange(1, 100);
				if (Ran <= 40)
				{
					Cast<ABellarusAIController>(Monster->GetAIController())->SetTailKey(true);
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				}
			}
		}

	}
}
