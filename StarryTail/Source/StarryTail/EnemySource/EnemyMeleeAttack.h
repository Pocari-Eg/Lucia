// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UEnemyMeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEnemyMeleeAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool IsAttacking = false;
};
