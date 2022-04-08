// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbShockEnd.h"
#include "../MbAIController.h"
#include "../../Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbShockEnd::UBTTaskMbShockEnd()
{
	NodeName = TEXT("ShockEnd");
}
EBTNodeResult::Type UBTTaskMbShockEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	Monster->OffShockDebuffEffect();

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsShockKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackedKey, false);

	return EBTNodeResult::Succeeded;
}