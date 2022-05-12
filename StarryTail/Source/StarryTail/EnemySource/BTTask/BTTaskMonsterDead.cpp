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

	return EBTNodeResult::InProgress;
}