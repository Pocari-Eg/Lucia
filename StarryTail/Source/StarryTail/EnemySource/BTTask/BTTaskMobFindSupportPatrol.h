// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../StarryTail.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobFindSupportPatrol.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMobFindSupportPatrol : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobFindSupportPatrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
