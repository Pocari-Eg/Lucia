// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbRotateToTarget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbRotateToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbRotateToTarget();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
