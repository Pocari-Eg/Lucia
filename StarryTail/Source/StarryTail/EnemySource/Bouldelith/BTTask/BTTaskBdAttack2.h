// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskBdAttack2.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBdAttack2 : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBdAttack2();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool bIsAttacking;
	bool bIsNotAttacking;
};
