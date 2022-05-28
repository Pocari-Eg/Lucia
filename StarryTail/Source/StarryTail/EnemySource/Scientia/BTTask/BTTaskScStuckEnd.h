// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskScStuckEnd.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskScStuckEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScStuckEnd();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
