// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/*
 원거리 공격 이펙트 - RangedAttackEffect
 근거리, 원거리, 돌진 공격 별 충돌체
 몬스터의 스폰 위치 - SpawnPos
 원거리 공격 횟수 - RangedAttackCount o
 원거리 공격 사거리 - RangedAttackRange o
 근거리 공격 사거리 - MeleeAttackRange o
 */
UCLASS()
class STARRYTAIL_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();
	virtual void OnPossess(APawn* InPawn) override;

	static const FName PlayerKey;
	static const FName RangedAttackCountKey;
	static const FName CanRangedAttackKey;
	static const FName CanMeleeAttackKey;

	static const float RangedAttackRange;
	static const float MeleeAttackRange;

	static int RangedAttackCount;
	static bool bCanRangedAttack;
	static bool bCanMeleeAttack;
private:
	UPROPERTY() //해당 멤버변수를 런타임도중 확인가능
	class UBehaviorTree* BTAsset;

	UPROPERTY()
	class UBlackboardData* BBAsset;
};
