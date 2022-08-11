// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobStopMove.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMobStopMove : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobStopMove();
private:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
