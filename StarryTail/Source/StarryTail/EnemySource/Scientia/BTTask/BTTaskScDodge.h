// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskScDodge.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskScDodge : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScDodge();
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

	float DodgeTimer;

	bool bIsDodge;
	bool bCanMove;
};
