// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskWingL.h"
#include "../Bellarus.h"
#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../BTService/BTServiceAttackJudge.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskWingL::UBTTaskWingL()
{
	NodeName = TEXT("WING_LATTACK");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskWingL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	Bellarus->PlayWingLAnim();
	Bellarus->GetAIController()->StopMovement();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellarus->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskWingL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

void UBTTaskWingL::SecondPhaseAction(ABellarus* Monster, UBehaviorTreeComponent& OwnerComp)
{
	FVector Center = Monster->GetLocation();
	Center -= FVector(0.0f, 0.0f, Monster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight());
	bool FirstJudge = UBTServiceAttackJudge::AttackJudge(Monster, Center, Monster->GetFirstJugdeRadius(), FColor::Green);
	if (FirstJudge)
	{
		auto Ran = FMath::RandRange(1, 100);
		if (Ran <= 40)
		{
			Cast<ABellarusAIController>(Monster->GetAIController())->SetWingRKey(true);
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
