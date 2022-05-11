// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBrokenEnd.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdBrokenEnd::UBTTaskBdBrokenEnd()
{
	NodeName = TEXT("BrokenEnd");
}
EBTNodeResult::Type UBTTaskBdBrokenEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBrokenKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttackedKey, false);

	return EBTNodeResult::Succeeded;
}