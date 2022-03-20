// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbFindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbFindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
