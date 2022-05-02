// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobGroggyEnd.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMobGroggyEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobGroggyEnd();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
