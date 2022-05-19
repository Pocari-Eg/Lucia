// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "ScAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AScAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	AScAIController();

	static const FName IsChangeKey;
	static const FName IsBattleWalkKey;

	static const FName IsAttack1Key;
	static const FName IsAttack2Key;
	static const FName IsAttack3Key;
private:
	void OnPossess(APawn* InPawn) override;
};
