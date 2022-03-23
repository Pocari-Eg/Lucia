// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbGroggyEnd.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbGroggyEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbGroggyEnd();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
