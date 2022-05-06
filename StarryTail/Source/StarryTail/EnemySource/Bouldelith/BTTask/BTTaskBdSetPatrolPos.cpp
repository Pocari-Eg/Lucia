// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdSetPatrolPos.h"
#include "../BdAIController.h"
#include "../Bouldelith.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "../../../StarryTail.h"

UBTTaskBdSetPatrolPos::UBTTaskBdSetPatrolPos()
{
	NodeName = TEXT("SetPatrolPos");
}

EBTNodeResult::Type UBTTaskBdSetPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (Result == EBTNodeResult::Failed)
		return EBTNodeResult::Failed;

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bouldelith)
		return EBTNodeResult::Failed;

	Bouldelith->GetPatrolList();

	for (auto Elem : Bouldelith->GetPatrolList())
	{
		if (Elem == Bouldelith->GetUsePatrol())
			continue;

		Bouldelith->SetUsePatrol(Elem);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABdAIController::PatrolPosKey, Elem->GetActorLocation());

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}