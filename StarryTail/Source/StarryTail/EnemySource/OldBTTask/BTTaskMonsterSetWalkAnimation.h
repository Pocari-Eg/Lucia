// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMonsterSetWalkAnimation.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMonsterSetWalkAnimation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMonsterSetWalkAnimation();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
