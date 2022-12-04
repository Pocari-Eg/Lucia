// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskScBattleIdle.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskScBattleIdle : public UBTTaskNode
{
	GENERATED_BODY()
private:
	UBTTaskScBattleIdle();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bIsCanDodge;
	bool bIsUseDodge;

	float WaitTime;
	float WaitTimer;
};
