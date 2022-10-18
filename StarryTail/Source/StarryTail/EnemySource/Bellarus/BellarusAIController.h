// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "BellarusAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API ABellarusAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	ABellarusAIController();
	
	void Attack() override;
	void Attacked()override;
	void Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback);

protected:
	virtual void OnPossess(APawn* InPawn) override;


private:
	int M_Attacked;
	int M_MaxAttacked;
};
