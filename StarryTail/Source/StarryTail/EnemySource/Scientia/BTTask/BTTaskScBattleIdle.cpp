// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScBattleIdle.h"
#include "../Scientia.h"
#include "../ScAIController.h"
#include "../../../PlayerSource/IreneFSM.h"

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

	bIsCanDodge = false;

	return EBTNodeResult::InProgress;
}
void UBTTaskScBattleIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	WaitTimer += DeltaSeconds;

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScAIController::PlayerKey));

	if (bIsUseDodge)
	{
		float Distance = Scientia->GetDistanceToPlayer();

		if (Distance < 500)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack2Key, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else if (Distance >= 500 && Distance < 1000)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack3Key, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		else if (Distance >= 1000)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack1Key, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
		bIsUseDodge = false;
		return;
	}

	if (Scientia->GetIsCanChange() && !Scientia->ScAttributeIsPlayerAttributeCounter() && Scientia->GetBarrierCount() > 1)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsChangeKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (Scientia->GetDistanceToPlayer() < 500 && Player->IreneState->IsSprintState())
	{
		bIsCanDodge = true;
	}

	if (bIsCanDodge && Scientia->GetDistanceToPlayer() < 200)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsDodgeKey, true);
		bIsUseDodge = true;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (WaitTimer >= WaitTime)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsBattleWalkKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}