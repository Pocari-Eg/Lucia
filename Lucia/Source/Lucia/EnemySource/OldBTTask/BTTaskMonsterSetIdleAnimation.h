// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMonsterSetIdleAnimation.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMonsterSetIdleAnimation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMonsterSetIdleAnimation();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
