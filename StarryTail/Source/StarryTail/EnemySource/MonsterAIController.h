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

	virtual void Attacked() {};
	virtual void  Attacked(EAttackedDirection AttackedDirection, EAttackedPower AttackedPower, bool bIsPlayerUseMana, bool bIsKnockback) {};
	virtual void Attack() {};

	void SetSpawnPos(FVector Position);
	void SetInAttackArea(bool Set);
	void SetAttackCoolKey(bool Set);


	//func===========================================
	void SetNormalState(bool State);
	void SetBattleState(bool State);
	void SetAttackedState(bool State);
	void SetSupportState(bool State);

	//key=======================================================================
	static const FName SpawnPosKey;
	static const FName PatrolPosKey;

	static const FName IsFindKey;
	static const FName PlayerKey;
	static const FName TraceRangeKey;

	static const FName MeleeAttackRangeKey;
	static const FName IsInAttackAreaKey;

	static const FName IsAttackCoolKey;
	static const FName IsAttackingKey;

	static const FName IsAttackedKey;
	static const FName IsGroggyKey;

	static const FName IsDeadKey;
	static const FName ReturnKey;



	//
	static const FName NormalStateKey;
	static const FName BattleStateKey;
	static const FName AttackedStateKey;
	static const FName SupportStateKey;

	static const FName Attack1Key;
	static const FName Attack2Key;
	static const FName Attack3Key;
protected:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;


	virtual void OnPossess(APawn* InPawn) override;
};
