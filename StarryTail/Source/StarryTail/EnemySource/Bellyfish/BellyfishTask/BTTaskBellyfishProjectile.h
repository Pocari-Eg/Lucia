// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Bellyfish.h"
#include "BTTaskBellyfishProjectile.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBellyfishProjectile : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskBellyfishProjectile();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool bIsAttacking;
};
