// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScStuckEnd.h"
#include "../Scientia.h"
#include "../ScAIController.h"

UBTTaskScStuckEnd::UBTTaskScStuckEnd()
{
	NodeName = TEXT("StuckEnd");
}
EBTNodeResult::Type UBTTaskScStuckEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsStuckKey, false);

	return EBTNodeResult::Succeeded;
}