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
	//���Ÿ� ������ 3ȸ �õ��� ���� ������ �������� Ȯ��
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
