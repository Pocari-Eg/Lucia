// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsCanRushAttack.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UIsCanRushAttack : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UIsCanRushAttack();

protected:
	//원거리 공격을 3회 시도해 돌진 공격이 가능한지 확인
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
