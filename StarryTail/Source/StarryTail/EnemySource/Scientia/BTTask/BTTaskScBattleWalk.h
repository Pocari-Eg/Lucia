// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NavigationSystem.h"
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

	UNavigationSystemV1* NavSys;
	ANavigationData* NavData;

	TSubclassOf<UNavigationQueryFilter> FilterClass;
	FSharedConstNavQueryFilter QueryFilter;
	FPathFindingQuery MyAIQuery;

	FVector NewLocation;

	bool bCanMove;

	int MoveRandom;
	int DirValue;

	float WaitTime;
	float WaitTimer;
};
