// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbAttackedEnd.h"
#include "../Morbit.h"
#include "../MbAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskMbAttackedEnd::UBTTaskMbAttackedEnd()
{
	NodeName = TEXT("MbAttackEnd");
}
EBTNodeResult::Type UBTTaskMbAttackedEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackedKey, false);

	return EBTNodeResult::Succeeded;
}