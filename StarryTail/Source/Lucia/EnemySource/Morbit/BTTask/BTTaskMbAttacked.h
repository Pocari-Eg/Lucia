// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbAttacked.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMbAttacked : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbAttacked();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	bool bIsAttacked;
	float WaitTimer;
	float WaitTime;
};
