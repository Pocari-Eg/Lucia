// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Lucia.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobFindSupportPatrol.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMobFindSupportPatrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobFindSupportPatrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
