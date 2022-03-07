// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UMoveToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMoveToPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool bIsArrive;
};
