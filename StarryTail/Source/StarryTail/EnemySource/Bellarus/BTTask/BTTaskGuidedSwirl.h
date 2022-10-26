// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskGuidedSwirl.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskGuidedSwirl : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskGuidedSwirl();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bIsAttacking;
};
