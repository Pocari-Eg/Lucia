// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskWingR.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskWingR : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskWingR();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SecondPhaseAction(class ABellarus* Monster, UBehaviorTreeComponent& OwnerComp);

	bool bIsAttacking;
	bool bIsNotAttacking;
};
