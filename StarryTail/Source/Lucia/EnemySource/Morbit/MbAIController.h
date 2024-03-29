// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "MbAIController.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API AMbAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AMbAIController();
	void Attack()override;
	void Attacked()override;
	void Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback) override;
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
