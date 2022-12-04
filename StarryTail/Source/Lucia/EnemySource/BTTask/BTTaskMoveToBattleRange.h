// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Monster.h"
#include "BTTaskMoveToBattleRange.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMoveToBattleRange : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskMoveToBattleRange();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
