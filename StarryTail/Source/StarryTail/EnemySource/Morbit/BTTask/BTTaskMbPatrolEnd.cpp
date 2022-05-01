// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbPatrolEnd.h"
#include "../MbAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbPatrolEnd::UBTTaskMbPatrolEnd()
{
	NodeName = TEXT("PatrolEnd");
}
EBTNodeResult::Type UBTTaskMbPatrolEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MbAIController = Cast<AMbAIController>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (MbAIController == nullptr)
	{
		STARRYLOG(Error, TEXT("Not Found MonsterController"));
		return EBTNodeResult::Failed;
	}

	MbAIController->SetPlayer();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);

	return EBTNodeResult::Succeeded;
}