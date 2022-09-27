// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleIdle.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdBattleIdle::UBTTaskBdBattleIdle()
{
	NodeName = TEXT("BattleIdle");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdBattleIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->BattleIdle();

	ChangeStateTime = FMath::RandRange(1, 3);

	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleIdle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ChangeStateTimer += DeltaSeconds;

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABdAIController::PlayerKey));

	
	if (Bouldelith->GetAttackFailedStack() >= 3 && Bouldelith->GetHpPercent() < 50)
	{
		Bouldelith->ResetAttackFailedStack();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Attack4Key, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, false);

		ChangeStateTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	if (Bouldelith->GetDistanceToPlayer() >= 500.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (Bouldelith->GetDistanceToPlayer() <= 200.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, false);

		if (Bouldelith->GetIsUseBackstep())
		{
			int Random = FMath::RandRange(0, 1);

			switch (Random)
			{
			case 0:
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Attack1Key, true);
				break;
			case 1:
				OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Attack2Key, true);
				break;
			}
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBackstepKey, true);
		}

		ChangeStateTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	if (ChangeStateTimer >= ChangeStateTime)
	{	
		int Random = FMath::RandRange(0, 2);

		switch (Random)
		{
		case 0:
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleWalkKey, true);
			break;
		case 1:
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Attack1Key, true);
			break;
		case 2:
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::Attack2Key, true);
			break;
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, false);

		ChangeStateTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
}