// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdWallGroggyEnd.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdWallGroggyEnd::UBTTaskBdWallGroggyEnd()
{
	NodeName = TEXT("WallGroggyEnd");
}
EBTNodeResult::Type UBTTaskBdWallGroggyEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsGroggyKey, false);




	return EBTNodeResult::Succeeded;
}