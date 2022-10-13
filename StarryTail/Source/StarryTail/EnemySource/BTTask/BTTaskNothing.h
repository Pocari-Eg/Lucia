// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNothing.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskNothing : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNothing();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
