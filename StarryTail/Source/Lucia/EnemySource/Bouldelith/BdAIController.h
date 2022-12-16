// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "BdAIController.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API ABdAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	ABdAIController();
	
	void Attack()override;
	void WallGroggy();
	void Attacked();
	void Broken();

	void SetBattleRunKey(bool state);
	void SetWalkPoint(FVector Location);
	static const FName IsBattleIdleKey;
	static const FName IsBattleWalkKey;

	static const FName IsWallGroggyKey;

	static const FName IsBattleRunKey;
	static const FName IsWalkPointKey;

	static const FName B_WalkLeftKey;
	static const FName B_WalkRightKey;

	static const FName Attack5Key;

private:
	void OnPossess(APawn* InPawn) override;
};
