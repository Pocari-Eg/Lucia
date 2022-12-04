// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Monster.h"
#include "BTTaskMobMoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMobMoveToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
private:
	AIreneCharacter* Player;

	float FollowSeconds;

	float PlayerFollowTime;
	float PlayerFollowTimer;

	float AttackTime;
	float AttackTimer;
public:
	UBTTaskMobMoveToPlayer();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
