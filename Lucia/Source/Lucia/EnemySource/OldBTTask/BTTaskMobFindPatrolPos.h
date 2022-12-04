// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Lucia.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobFindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMobFindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobFindPatrolPos();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
