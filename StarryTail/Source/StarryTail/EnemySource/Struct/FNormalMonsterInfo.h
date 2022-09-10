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


	//Stat
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EEnemyRank M_Type; // ���� ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // ���� Ű��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Max_HP; //ü��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float M_HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_MoveSpeed; //�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Type; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Chain_Detect_Radius; // �����̺�� Ʈ�� Detect ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Player_Energy;


	//Skill
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Code;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Range; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Skill_Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Skill_Atk; //���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Skill_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Skill_Set_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Skill_Cool; // ���� Ű��



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_MaxAttacked; // ���� Ű��
	//etc
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


	//Shield;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="ManaShield")
	int Max_Ele_Shield;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ManaShield")
	TArray<FElementalShield> Ele_Shield; // ���� ���
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

	//�þ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Sight_Radius; //�þ߰Ÿ�
	UPROPERTY()
		float M_Sight_Angle; //�þ߰�
	UPROPERTY()
		float M_Sight_Height;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Angle; //�þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Radius; //�þ߰Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Atk_Height;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //���ݻ�Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //�ִ� ���� �Ÿ�

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
struct FMonsterSkillInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int M_Skill_Code;
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
};

