// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobPatrolEnd.h"
#include "../MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMobPatrolEnd::UBTTaskMobPatrolEnd()
{
	NodeName = TEXT("PatrolEnd");
}
EBTNodeResult::Type UBTTaskMobPatrolEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MonsterAIController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	if (MonsterAIController == nullptr)
	{
		STARRYLOG(Error, TEXT("Not Found MonsterController"));
		return EBTNodeResult::Failed;
	}

	MonsterAIController->SetPlayer();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);

	return EBTNodeResult::Succeeded;
}