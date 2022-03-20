// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMbAttack.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMbAttack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMbAttack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSecons) override;
private:
	bool bIsAttacking;
};
