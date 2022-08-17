// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskStrainRunEnd.h"
#include "../StrainAIController.h"
#include "../Strain.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskStrainRunEnd::UBTTaskStrainRunEnd()
{
	NodeName = TEXT("StrainRunEnd");
}
EBTNodeResult::Type UBTTaskStrainRunEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Strain = Cast<AStrain>(OwnerComp.GetAIOwner()->GetPawn());

	Strain->GetAIController()->StopMovement();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsRunKey, false);
	return EBTNodeResult::Succeeded;
}
