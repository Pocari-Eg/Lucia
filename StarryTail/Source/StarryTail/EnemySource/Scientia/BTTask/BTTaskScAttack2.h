// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NavigationSystem.h"
#include "BTTaskScAttack2.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskScAttack2 : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScAttack2();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UNavigationSystemV1* NavSys;
	ANavigationData* NavData;

	TSubclassOf<UNavigationQueryFilter> FilterClass;
	FSharedConstNavQueryFilter QueryFilter;
	FPathFindingQuery MyAIQuery;


	bool bIsAttacking;
	bool bIsMove;
	bool bCanMove;
	bool bIsClawPre;

	FVector MoveDir;
	FVector NewLocation;
	int AttackCount;
};
