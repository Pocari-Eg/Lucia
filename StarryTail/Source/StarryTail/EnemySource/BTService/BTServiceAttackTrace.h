// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Components/LineBatchComponent.h"
#include "../Monster.h"
#include "BTServiceAttackTrace.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTServiceAttackTrace : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceAttackTrace();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	void Attack1Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center, FVector CenterBottom, FVector CenterTop);
	void Attack2Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center, FVector CenterBottom, FVector CenterTop);
	void Attack3Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center, FVector CenterBottom, FVector CenterTop);
};


