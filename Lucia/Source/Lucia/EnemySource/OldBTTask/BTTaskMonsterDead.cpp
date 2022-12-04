// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterDead.h"
#include "../Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMonsterDead::UBTTaskMonsterDead()
{
	NodeName = TEXT("Dead");
}
EBTNodeResult::Type UBTTaskMonsterDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackCoolKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsInAttackAreaKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackedKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);

	return EBTNodeResult::InProgress;
}