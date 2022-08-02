// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskFernoRunEnd.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskFernoRunEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskFernoRunEnd();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
