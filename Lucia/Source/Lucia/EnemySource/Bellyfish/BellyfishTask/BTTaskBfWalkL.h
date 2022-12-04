// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBfWalkL.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskBfWalkL : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBTTaskBfWalkL();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	float WalkTime;
	float WalkTimer;
};
