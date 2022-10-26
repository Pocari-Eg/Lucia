// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskTail.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskTail : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskTail();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void SecondPhaseAction(class ABellarus* Monster , UBehaviorTreeComponent& OwnerComp);

	bool bIsAttacking;
	bool bIsNotAttacking;
};
