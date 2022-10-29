// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNothing.h"
#include"../Monster.h"
#include"../MonsterAIController.h"

UBTTaskNothing::UBTTaskNothing()
{
	NodeName = TEXT("Nothing");

}

EBTNodeResult::Type UBTTaskNothing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetAIController()->StopMovement();
	return EBTNodeResult::InProgress;
}
