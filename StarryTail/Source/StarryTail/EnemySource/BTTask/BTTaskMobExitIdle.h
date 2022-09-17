// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobExitIdle.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMobExitIdle : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobExitIdle();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};



