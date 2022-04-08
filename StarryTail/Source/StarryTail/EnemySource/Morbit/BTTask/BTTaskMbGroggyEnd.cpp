// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbGroggyEnd.h"
#include "../MbAIController.h"
#include "../../Monster.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskMbGroggyEnd::UBTTaskMbGroggyEnd()
{
	NodeName = TEXT("GroggyEnd");
}
EBTNodeResult::Type UBTTaskMbGroggyEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	Monster->ResetDef();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsGroggyKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsShockKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackedKey, false);

	return EBTNodeResult::Succeeded;
}