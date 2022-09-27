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
	
	void Attack()override;
	void WallGroggy();
	void Attacked();
	void Broken();
	void SetStatueKey(bool state);

	static const FName IsBattleIdleKey;
	static const FName IsBattleWalkKey;

	static const FName IsBackstepKey;


	static const FName IsBrokenKey;
	static const FName IsWallGroggyKey;

	static const FName IsStatueStateKey;

private:
	void OnPossess(APawn* InPawn) override;
};
