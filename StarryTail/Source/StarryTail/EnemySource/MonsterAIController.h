// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"
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
	void SetTraceKey(bool State);
	void SetShieldKey(bool State);
	void OnAttack(int i);
	void OffAttack(int i);
	void SetBackStepKey(bool State);

	void SetBattleMonster(AActor* Monster);
	void InitBattleMonster();

	bool GetIsAttacking();
	bool GetIsTraceState();

	//debug

	ULineBatchComponent* GetDebugLineBatcher(const UWorld* InWorld, bool bPersistentLines, float LifeTime, bool bDepthIsForeground);

	static float GetDebugLineLifeTime(ULineBatchComponent* LineBatcher, float LifeTime, bool bPersistent);


	 void DrawRadial(const UWorld* _InWorld,
		const FMatrix& _TransformMatrix,
		float _Radius,
		float _Angle,
		const FColor& _Color,
		int32 _Segments,
		float _LifeTime,
		bool _bPersistentLines,
		uint8 _DepthPriority,
		float _Thickness);

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

	static const FName B_IdleKey;

	//
	static const FName NormalStateKey;
	static const FName BattleStateKey;
	static const FName AttackedStateKey;
	static const FName SupportStateKey;

	static const FName Attack1Key;
	static const FName Attack2Key;
	static const FName Attack3Key;
	static const FName Attack4Key;

	static const FName BattleMonsterKey;
	static const FName IsShieldOnKey;
	static const FName TraceStateKey;


	static const FName IsBackStepOnKey;
protected:
	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;


	virtual void OnPossess(APawn* InPawn) override;
};
