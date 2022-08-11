// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskStrainAttacked.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskStrainAttacked : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskStrainAttacked();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	bool bIsAttacked;
	float WaitTimer;
	float WaitTime;
};
