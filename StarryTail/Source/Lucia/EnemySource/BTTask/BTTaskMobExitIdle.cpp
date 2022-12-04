// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobExitIdle.h"
#include "../MonsterAIController.h"
#include "BTTaskMobExitIdle.h"

UBTTaskMobExitIdle::UBTTaskMobExitIdle()
{
	NodeName = TEXT("ExitIdle");
}

EBTNodeResult::Type UBTTaskMobExitIdle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::B_IdleKey, false);
	return EBTNodeResult::Succeeded;
}
