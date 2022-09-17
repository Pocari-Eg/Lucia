// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "Engine/DataTable.h"
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
struct FAttackRange
{
	GENERATED_BODY()
public:
	//공격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Angle; //시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Radius; //시야거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Height;
};
USTRUCT(Atomic, BluePrintType)
struct FNormalMonsterInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Monster_Code; // 몬스터 키값

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // 몬스터 키값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Max_HP; //체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float M_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_MoveSpeed; //이동속도
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_01; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_02;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_03;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int Weapon_Soul;





	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Range; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Atk; //공격력
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Time;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Set_Time;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Cool; // 몬스터 키값

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float S_Attack_Time; // 몬스터 키값

	//Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEnemyRank Monster_Rank; // 몬스터 등급

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack1Range;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack2Range;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack3Range;

	//시야
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Sight_Radius; //시야거리
	UPROPERTY()
		float M_Sight_Angle; //시야각
	UPROPERTY()
		float M_Sight_Height;




	//etc

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_MaxAttacked;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Chain_Detect_Radius; // 비헤이비어 트리 Detect 몬스터 전이 범위

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute; // 몬스터 속성
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //전투시 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeadWaitTime; // 사망시 사라지는 대기시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PatrolArea;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_MaxFollowTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_AttackPercent;
//



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //공격사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //최대 추적 거리

public:
	//메인 속성 방어력들을 저장 20220414 수정
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttributeKeyword CurrentDebuffAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultBattleWalkMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultAnimePlayRate;


	//shield

		//Shield;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ManaShield")
		int Max_Ele_Shield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ManaShield")
		TArray<FElementalShield> Ele_Shield; 
	int Ele_Shield_Count;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ManaShield")
		bool bIsShieldOn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ManaShield")
		int ManaShieldDec;
};

USTRUCT(Atomic, BluePrintType)
struct FMonsterSkillDataTable :public FTableRowBase
{
	GENERATED_BODY();
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int M_Skill_Range;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float M_Skill_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int M_Skill_Atk;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float M_Skill_Time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float M_Skill_Set_Time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float M_Skill_Cool;
	//공격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Angle; //시야각
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Radius; //시야거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Height;
};
USTRUCT(Atomic, BluePrintType)
struct FMonsterDataTable :public FTableRowBase
{
	GENERATED_BODY();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // 몬스터 키값
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Max_HP; //체력
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float M_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_MoveSpeed; //이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Weapon_Soul;
};
