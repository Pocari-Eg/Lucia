// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsInRangedAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UIsInRangedAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UIsInRangedAttackRange();

protected:
	//���Ÿ� ���� ���� ���� �ִ� �÷��̾� Ȯ��
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
