// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "../Monster.h"
#include "BTTaskMobMoveToPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMobMoveToPatrolPos : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTaskMobMoveToPatrolPos();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


};
