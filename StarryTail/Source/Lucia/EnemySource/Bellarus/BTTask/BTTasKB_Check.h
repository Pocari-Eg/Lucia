// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../../Monster.h"
#include "BTTasKB_Check.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTasKB_Check : public UBTTaskNode
{
	GENERATED_BODY()
private:
	FVector MoveDirection;
	float CheckTimer;
	float ShieldOffCheckTime;
public:
	UBTTasKB_Check();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void MeleeAttck(class ABellarus* Bellarus, FVector Center, UBehaviorTreeComponent& OwnerComp);
};
