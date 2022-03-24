// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../IreneCharacter.h"
#include "MonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterAIController();
	virtual void OnPossess(APawn* InPawn) override;

	void Init();

	void SetPlayer();
	void SetFind();

	void Attacked();
	void Groggy();
	void Shock();

	static const FName SpawnPosKey;
	static const FName PatrolPosKey;

	static const FName IsFindKey;
	static const FName PlayerKey;
	static const FName TraceRangeKey;

	static const FName MeleeAttackRangeKey;
	static const FName CanMeleeAttackKey;
	static const FName IsAttackingKey;

	static const FName IsAttackedKey;
	static const FName IsGroggyKey;
	static const FName IsShockKey;

	static const FName ReturnKey;
protected:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;
};
