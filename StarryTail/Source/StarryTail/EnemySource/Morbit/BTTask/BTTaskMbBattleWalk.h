// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbBattleWalk.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbBattleWalk : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbBattleWalk();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
