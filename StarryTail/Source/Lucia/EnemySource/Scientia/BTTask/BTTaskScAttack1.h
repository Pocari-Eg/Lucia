// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskScAttack1.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskScAttack1 : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScAttack1();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bIsAttacking;
	bool bIsPre;

	float WaitTimer;
	float WaitTime;
};
