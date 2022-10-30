// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNothing.h"
#include"../Monster.h"
#include"../MonsterAIController.h"

UBTTaskNothing::UBTTaskNothing()
{
	NodeName = TEXT("Nothing");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskNothing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->PlayIdleAnim();

	Monster->GetAIController()->StopMovement();
	return EBTNodeResult::InProgress;
}

void UBTTaskNothing::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());


	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::SupportStateKey)==true)
	{
		Monster->RotationPlayer(DeltaSeconds);
	}
}
