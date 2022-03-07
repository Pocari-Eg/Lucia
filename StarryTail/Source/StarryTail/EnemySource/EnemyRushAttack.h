// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "EnemyRushAttack.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UEnemyRushAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UEnemyRushAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool IsAttacking = false;
};
