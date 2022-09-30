// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskWalkLR.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskWalkLR : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBTTaskWalkLR();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
