// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NavigationSystem.h"
#include "BTTaskScAttack3.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskScAttack3 : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScAttack3();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UNavigationSystemV1* NavSys;
	ANavigationData* NavData;

	TSubclassOf<UNavigationQueryFilter> FilterClass;
	FSharedConstNavQueryFilter QueryFilter;
	FPathFindingQuery MyAIQuery;

	FVector MoveDir;
	FVector NewLocation;

	FVector StartLocation;

	bool bCanMove;
	bool bIsTurn;
	bool bIsRush;

	float RushTimer;
	float TurnCoolTimer;
};
