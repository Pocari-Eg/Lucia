// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../StarryTail.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Monster.h"
#include "BTTaskWalkState.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskWalkState : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskWalkState();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void FindPatrolPos(AMonster* Monster);
private:

	bool Wait;

	float WalkTimer;
	float WalkTime;

	float WaitTimer;
	float WaitTime;
};
