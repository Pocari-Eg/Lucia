// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TurnToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UTurnToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UTurnToPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
