// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbReturnEnded.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbReturnEnded : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbReturnEnded();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
