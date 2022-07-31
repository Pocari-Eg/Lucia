// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "FernoAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AFernoAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AFernoAIController();
	


	void Attacked()override;
	void Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback);

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	static const FName IsCanRangeAttackKey;
private:
	int M_Attacked;
	int M_MaxAttacked;
};
