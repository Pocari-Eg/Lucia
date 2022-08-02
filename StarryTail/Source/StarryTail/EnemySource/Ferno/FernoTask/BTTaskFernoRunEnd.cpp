// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFernoRunEnd.h"
#include "../FernoAIController.h"
#include "../Ferno.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskFernoRunEnd::UBTTaskFernoRunEnd()
{
	NodeName = TEXT("FernoRunEnd");
}
EBTNodeResult::Type UBTTaskFernoRunEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Ferno = Cast<AFerno>(OwnerComp.GetAIOwner()->GetPawn());

	Ferno->GetAIController()->StopMovement();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsRunKey, false);
	return EBTNodeResult::Succeeded;
}
