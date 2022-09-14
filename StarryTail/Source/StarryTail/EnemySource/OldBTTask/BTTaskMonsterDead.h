// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMonsterDead.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMonsterDead : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMonsterDead();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
