// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobReturnEnded.h"
#include "../MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMobReturnEnded::UBTTaskMobReturnEnded()
{
	NodeName = TEXT("ReturnEnded");
}
EBTNodeResult::Type UBTTaskMobReturnEnded::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::ReturnKey, false);

	return EBTNodeResult::Succeeded;
}
