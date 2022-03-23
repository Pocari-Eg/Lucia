// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbAttackedEnd.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbAttackedEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbAttackedEnd();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
