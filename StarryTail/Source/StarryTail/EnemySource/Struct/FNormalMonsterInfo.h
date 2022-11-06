// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "Engine/DataTable.h"
#include "FNormalMonsterInfo.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FAttackRange
{
	GENERATED_BODY()
public:
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Angle; //�þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Radius; //�þ߰Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Height;
};
USTRUCT(Atomic, BluePrintType)
struct FNormalMonsterInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Monster_Code; // ���� Ű��

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // ���� Ű��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Max_HP; //ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float M_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_MoveSpeed; //�̵��ӵ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_01; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_02;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_03;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Type_04;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_05;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_06;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_07;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_08;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Spirit_Soul;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Shield_Def;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Battle_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Support_Radius;


	//Attacked Time
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float M_Attacked_Time;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Range; 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int M_Skill_Atk; //���ݷ�
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Time;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Set_Time;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float M_Skill_Cool; // ���� Ű��

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float S_Attack_Time; // ���� Ű��

	//Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEnemyRank Monster_Rank; // ���� ���

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack1Range;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack2Range;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack3Range;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FAttackRange Attack4Range;
	//�þ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Sight_Radius; //�þ߰Ÿ�
	UPROPERTY()
		float M_Sight_Angle; //�þ߰�
	UPROPERTY()
		float M_Sight_Height;

	//Stack

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Stack")
	int MaxStackCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stack")
	int CurStackCount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stack")
	float StackDamage;
	int OverStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stack")
	float StackCheckTime;
	float StackCheckTimer;

	bool bIsStackCheck;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stack")
	float StackEnableDistance;




	//etc
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float M_FSM_DPS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_MaxAttacked;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Chain_Detect_Radius; // �����̺�� Ʈ�� Detect ���� ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute; // ���� �Ӽ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //������ �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeadWaitTime; // ����� ������� ���ð�
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
	float M_AttackTraceInterver;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //���ݻ�Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //�ִ� ���� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotationRate; //�ִ� 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSupportWalkTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSupportWalkTime;

public:
	//���� �Ӽ� ���µ��� ���� 20220414 ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttributeKeyword CurrentDebuffAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultBattleWalkMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultAnimePlayRate;

};

USTRUCT(Atomic, BluePrintType)
struct FMonsterSkillDataTable :public FTableRowBase
{
	GENERATED_BODY();
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int M_Skill_Type;
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
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Angle; //�þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Radius; //�þ߰Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Height;
};
USTRUCT(Atomic, BluePrintType)
struct FMonsterDataTable :public FTableRowBase
{
	GENERATED_BODY();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // ���� Ű��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Max_HP; //ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float M_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_MoveSpeed; //�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_01;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_02;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_03;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type_04;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_05;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_06;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_07;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Skill_Type_08;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Spirit_Soul;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int M_Shield_Def;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Battle_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Support_Radius;
};
