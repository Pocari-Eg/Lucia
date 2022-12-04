// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdWallGroggyEnd.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskBdWallGroggyEnd : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdWallGroggyEnd();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
