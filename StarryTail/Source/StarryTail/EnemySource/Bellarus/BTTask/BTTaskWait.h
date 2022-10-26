// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskWait.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskWait : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskWait();


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void SecondPhaseAction(class ABellarus* Monster, UBehaviorTreeComponent& OwnerComp);
	float WaitTimer;
	bool Wait;
};
