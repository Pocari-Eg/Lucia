// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishRunEnd.h"
#include "../BellyfishAIController.h"
#include "../Bellyfish.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskBellyfishRunEnd::UBTTaskBellyfishRunEnd()
{
	NodeName = TEXT("BellyfishRunEnd");
}
EBTNodeResult::Type UBTTaskBellyfishRunEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());

	Bellyfish->GetAIController()->StopMovement();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsRunKey, false);
	return EBTNodeResult::Succeeded;
}
