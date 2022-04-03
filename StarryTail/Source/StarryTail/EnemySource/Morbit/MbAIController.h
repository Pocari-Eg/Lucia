// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "MbAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AMbAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AMbAIController();
	void SetMilitantAI();
	void SetDefensiveAI();
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
