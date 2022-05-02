// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterDead.h"
#include "../Monster.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMonsterDead::UBTTaskMonsterDead()
{
	NodeName = TEXT("Dead");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMonsterDead::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}