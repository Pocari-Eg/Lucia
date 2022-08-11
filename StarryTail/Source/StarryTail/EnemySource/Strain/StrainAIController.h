// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "StrainAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AStrainAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AStrainAIController();
	
	void Attack() override;
	void Attacked()override;
	void Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback);

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:

	static const FName IsAfterAttacked;

private:
	int M_Attacked;
	int M_MaxAttacked;
};
