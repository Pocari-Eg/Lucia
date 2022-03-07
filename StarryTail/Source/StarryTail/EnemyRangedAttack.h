// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyRangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UEnemyRangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEnemyRangedAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool IsAttacking = false;
};
