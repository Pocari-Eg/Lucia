// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMobReturnEnded.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMobReturnEnded : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMobReturnEnded();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
