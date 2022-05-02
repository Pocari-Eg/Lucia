// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobGroggyEnd.h"
#include "../MonsterAIController.h"
#include "../Monster.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskMobGroggyEnd::UBTTaskMobGroggyEnd()
{
	NodeName = TEXT("GroggyEnd");
}
EBTNodeResult::Type UBTTaskMobGroggyEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	Monster->ResetDef();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsGroggyKey, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackedKey, false);

	return EBTNodeResult::Succeeded;
}