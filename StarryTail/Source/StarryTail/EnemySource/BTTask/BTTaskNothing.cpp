// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNothing.h"

UBTTaskNothing::UBTTaskNothing()
{
	NodeName = TEXT("Nothing");
}

EBTNodeResult::Type UBTTaskNothing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}
