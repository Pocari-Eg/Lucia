// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FNormalMonsterInfo.generated.h"


USTRUCT(Atomic, BluePrintType)
struct FNormalMonsterInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Code; // 몬스터 키값
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHp; //체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Atk; //공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Def; //기본 방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed; //이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //전투시 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewAngle; //시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewRange; //시야거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //공격사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //최대 추적 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute; // 몬스터 속성
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DetectMonsterRange; // 비헤이비어 트리 Detect 몬스터 전이 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArbitraryConstValueA; // 임의의 상수 A
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArbitraryConstValueB; // 임의의 상수 B
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArbitraryConstValueC; // 임의의 상수 C
public:
	//메인 속성 방어력들을 저장
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<EAttributeKeyword> MainAttributeDef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttributeKeyword CurrentDebuffAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentDef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultBattleWalkMoveSpeed;
};
