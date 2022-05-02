// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdSetPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBdSetPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdSetPatrolPos();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
