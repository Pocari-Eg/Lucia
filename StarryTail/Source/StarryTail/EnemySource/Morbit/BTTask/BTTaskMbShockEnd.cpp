// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbShockEnd.h"
#include "../MbAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbShockEnd::UBTTaskMbShockEnd()
{
	NodeName = TEXT("ShockEnd");
}
EBTNodeResult::Type UBTTaskMbShockEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsShockKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackedKey, false);

	return EBTNodeResult::Succeeded;
}