// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobStopMove.h"
#include "../MonsterAIController.h"
#include "../Monster.h"

UBTTaskMobStopMove::UBTTaskMobStopMove()
{
	NodeName = TEXT("StopMove");
}

EBTNodeResult::Type UBTTaskMobStopMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;


	Monster->GetAIController()->StopMovement();

	return EBTNodeResult::Succeeded;
}
