// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbReturnEnded.h"
#include "../MbAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbReturnEnded::UBTTaskMbReturnEnded()
{
	NodeName = TEXT("ReturnEnded");
}
EBTNodeResult::Type UBTTaskMbReturnEnded::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::ReturnKey, false);

	return EBTNodeResult::Succeeded;
}
