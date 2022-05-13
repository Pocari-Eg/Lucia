// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleRun.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

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
	
	BattleRunTimer = 0.0f;

	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleRun::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABdAIController::PlayerKey));

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Bouldelith->GetController(), Player->GetActorLocation());

	BattleRunTimer += DeltaSeconds;

	if (BattleRunTimer >= 4.0f)
	{
		if (Bouldelith->GetBattleRunSpeed() < 700.0f)
		{
			Bouldelith->AddBattleRunSpeed(150);
			Bouldelith->UpgradeBattleRunAnim();
		}
		BattleRunTimer = 0.0f;
	}

	if (Bouldelith->GetDistanceToPlayer() >= 3000.0f)
	{
		Bouldelith->Walk();
		Bouldelith->SetIsBattleState(false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::ReturnKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABdAIController::PlayerKey, nullptr);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (Bouldelith->GetDistanceToPlayer() >= 2500.0f)
	{
		bIsAway = true;
	}
	else if (Bouldelith->GetDistanceToPlayer() <= 1000.0f && bIsAway && !Bouldelith->GetIsChangeBattleRunStateToAttackedState())
	{
		Bouldelith->SetIsChangeBattleRunStateToAttackedState(false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack3Key, true);
		bIsAway = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (Bouldelith->GetDistanceToPlayer() <= 1000.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		bIsAway = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}