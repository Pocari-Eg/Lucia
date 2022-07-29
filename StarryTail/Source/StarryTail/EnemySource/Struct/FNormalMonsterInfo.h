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
		EEnemyRank M_Type; // ���� ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int M_Atk_Type; // ���� Ű��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Max_HP; //ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Atk; //���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_MoveSpeed; //�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //������ �̵��ӵ�
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute; // ���� �Ӽ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DetectMonsterRange; // �����̺�� Ʈ�� Detect ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeadWaitTime; // ����� ������� ���ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackPower;
	


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

	//attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewAngle; //�þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewRange; //�þ߰Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //���ݻ�Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //�ִ� ���� �Ÿ�

public:
	//���� �Ӽ� ���µ��� ���� 20220414 ����
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
