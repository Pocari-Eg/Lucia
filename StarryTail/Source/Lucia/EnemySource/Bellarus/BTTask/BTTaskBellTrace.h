// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Bellarus.h"
#include "BTTaskBellTrace.generated.h"

/**
 *
 */
UCLASS()
class LUCIA_API UBTTaskBellTrace : public UBTTaskNode
{
	GENERATED_BODY()
private:

	bool bIsMove;
public:
	UBTTaskBellTrace();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
