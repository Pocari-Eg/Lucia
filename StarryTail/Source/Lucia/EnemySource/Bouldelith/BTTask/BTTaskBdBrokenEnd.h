// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdBrokenEnd.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskBdBrokenEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdBrokenEnd();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
