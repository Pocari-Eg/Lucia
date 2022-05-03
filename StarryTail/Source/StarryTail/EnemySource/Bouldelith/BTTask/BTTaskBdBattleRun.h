// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdBattleRun.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBdBattleRun : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdBattleRun();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float BattleRunTimer;
};
