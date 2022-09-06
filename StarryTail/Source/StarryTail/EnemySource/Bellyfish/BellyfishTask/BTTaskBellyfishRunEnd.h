// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBellyfishRunEnd.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBellyfishRunEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBellyfishRunEnd();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
