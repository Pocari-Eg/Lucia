// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskScChange.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskScChange : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskScChange();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bIsChange;
};
