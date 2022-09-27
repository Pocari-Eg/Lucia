// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"


#include "BTTaskPatrol.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	public:
		UBTTaskPatrol();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	private:
	bool bIsReturn;
	bool bIsIdle;
	bool bIsWalk;
	bool bIsSpawn;


	FVector WalkPoint;

	float Timer;
	float Time;
};
