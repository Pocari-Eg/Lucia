// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskScBattleWalk.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskScBattleWalk : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScBattleWalk();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	int MoveRandom;
	int DirValue;

	float WaitTime;
	float WaitTimer;
};
