// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Components/LineBatchComponent.h"
#include "BTServiceAttackJudge.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTServiceAttackJudge : public UBTService
{
	GENERATED_BODY()

private:
	float AttackCheckTimer;

	bool InFirstJudge;

	bool InTail;
	bool InWing_L;
	bool InWing_R;
public:
	UBTServiceAttackJudge();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool AttackJudge(class AMonster* Monster, FVector Center,float Radius);
	bool AttackCheck(class AMonster* Monster, FVector Center, float Radius,float Height,float Angle, float AttackAxis);

};


