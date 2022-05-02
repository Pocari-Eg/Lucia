// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobRotateToTarget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMobRotateToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobRotateToTarget();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
