// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbBattleIdle.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbBattleIdle : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbBattleIdle();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
