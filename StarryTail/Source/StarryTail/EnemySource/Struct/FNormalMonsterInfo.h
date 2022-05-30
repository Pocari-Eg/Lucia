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
		int Code; // ���� Ű��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHp; //ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Atk; //���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Def; //�⺻ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Barrier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed; //�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //������ �̵��ӵ�
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute; // ���� �Ӽ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DetectMonsterRange; // �����̺�� Ʈ�� Detect ���� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DeadWaitTime; // ����� ������� ���ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float KnockBackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArbitraryConstValueA; // ������ ��� A
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArbitraryConstValueB; // ������ ��� B
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ArbitraryConstValueC; // ������ ��� C
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float HalvedValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NormalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CriticalValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemyRank EnemyRank; // ���� ���
   
public:
	//���� �Ӽ� ���µ��� ���� 20220414 ����
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		// TArray<EAttributeKeyword> MainAttributeDef;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float DefaultAnimePlayRate;
};
