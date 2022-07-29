// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FNormalMonsterInfo.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FElementalShield
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int DEF;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttributeKeyword Type;

};
USTRUCT(Atomic, BluePrintType)
struct FNormalMonsterInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEnemyRank M_Type; // 몬스터 등급

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // 몬스터 키값
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Max_HP; //체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Atk; //공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_MoveSpeed; //이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //전투시 이동속도
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute; // 몬스터 속성
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DetectMonsterRange; // 비헤이비어 트리 Detect 몬스터 전이 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeadWaitTime; // 사망시 사라지는 대기시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackPower;
	


	//Shield;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="ManaShield")
	int Max_Ele_Shield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ManaShield")
	TArray<FElementalShield> Ele_Shield; // 몬스터 등급
	int Ele_Shield_Count;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ManaShield")
	bool bIsShieldOn;
   
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ManaShield")
	int ManaShieldDec;


	//Quill
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quill")
	int Quill_MaxStack;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quill")
	int Quill_CurStack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category = "Quill")
	int Quill_MaxStackDamage;

	//attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewAngle; //시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewRange; //시야거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //공격사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //최대 추적 거리

public:
	//메인 속성 방어력들을 저장 20220414 수정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttributeKeyword CurrentDebuffAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentHp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultBattleWalkMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultAnimePlayRate;
};
