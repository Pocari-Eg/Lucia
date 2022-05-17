// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScBattleIdle.h"
#include "../Scientia.h"
#include "../ScAIController.h"

UBTTaskScBattleIdle::UBTTaskScBattleIdle()
{
	NodeName = TEXT("BattleIdle");
	bNotifyTick = true;

	WaitTime = 2.0f;
}
EBTNodeResult::Type UBTTaskScBattleIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	WaitTimer = 0.0f;

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	Scientia->SetState(TEXT("BattleIdle"));

	Scientia->BattleIdle();


	return EBTNodeResult::InProgress;
}
void UBTTaskScBattleIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	WaitTimer += DeltaSeconds;

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	if (!Scientia->ScAttributeIsPlayerAttributeCounter() && Scientia->GetBarrierCount() > 1)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsChangeKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (WaitTimer >= WaitTime)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}