// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskWalkR.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskWalkR : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBTTaskWalkR();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	float WalkTime;
	float WalkTimer;
};
