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
class LUCIA_API UBTServiceAttackTrace : public UBTService
{
	GENERATED_BODY()

private:
	bool bIsAttack1In;
	bool bIsAttack2In;
	bool bIsAttack3In;

	bool bIsAttack12In;
	bool bIsAttack23In;
public:
	UBTServiceAttackTrace();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool Attack1Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center);
	bool Attack2Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center);
	bool Attack3Trace(AMonster* Monster, UBehaviorTreeComponent& OwnerComp, FVector Center);
};


