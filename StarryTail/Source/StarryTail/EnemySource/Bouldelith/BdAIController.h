// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "BdAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API ABdAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	ABdAIController();
	
	void WallGroggy();
	void Attacked();
	void Broken();

	static const FName IsBattleIdleKey;
	static const FName IsBattleWalkKey;

	static const FName IsBackstepKey;

	static const FName IsAttack1Key;
	static const FName IsAttack2Key;
	static const FName IsAttack3Key;
	static const FName IsAttack4Key;

	static const FName IsBrokenKey;
	static const FName IsWallGroggyKey;
private:
	void OnPossess(APawn* InPawn) override;
};
