// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleRun.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"

UBTTaskBdBattleRun::UBTTaskBdBattleRun()
{
	NodeName = TEXT("BattleRun");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdBattleRun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->BattleRun();

	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	BattleRunTimer += DeltaSeconds;

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	if (BattleRunTimer >= 2.0f)
	{
		if(Bouldelith->GetBattleRunSpeed() <= 500.0f)
			Bouldelith->AddBattleRunSpeed(100);
		BattleRunTimer = 0.0f;
	}

	if (Bouldelith->GetDistanceToPlayer() >= 1000.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABdAIController::PlayerKey, nullptr);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::ReturnKey, true);
		Bouldelith->ResetBattleRunSpeed();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}