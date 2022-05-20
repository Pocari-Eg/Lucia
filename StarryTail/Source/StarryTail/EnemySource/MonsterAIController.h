// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
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

	void SetPlayer();
	void SetFind();

	void Groggy();
	void Death();

	void SetSpawnPos(FVector Position);

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

	static const FName IsDeadKey;

	static const FName ReturnKey;
protected:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;

	virtual void OnPossess(APawn* InPawn) override;
};
