// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMonsterSetDetectAnimation.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMonsterSetDetectAnimation : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMonsterSetDetectAnimation();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
