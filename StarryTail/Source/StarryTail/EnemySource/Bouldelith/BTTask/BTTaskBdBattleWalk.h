// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdBattleWalk.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBdBattleWalk : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdBattleWalk();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	float ChangeStateTimer;
	float ChangeStateTime;
};
