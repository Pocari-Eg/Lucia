// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdWalkR.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskBdWalkR : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBTTaskBdWalkR();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	float WalkTime;
	float WalkTimer;
};
