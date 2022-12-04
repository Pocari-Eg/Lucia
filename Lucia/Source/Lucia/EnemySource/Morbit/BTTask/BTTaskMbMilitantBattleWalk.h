// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbMilitantBattleWalk.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMbMilitantBattleWalk : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbMilitantBattleWalk();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
