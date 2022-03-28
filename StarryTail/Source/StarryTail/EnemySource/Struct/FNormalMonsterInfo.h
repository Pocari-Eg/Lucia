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
		FName Name; //�̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHp; //ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Atk; //���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Def; //�⺻ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveSpeed; //�̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BattleWalkMoveSpeed; //������ �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewAngle; //�þ߰�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ViewRange; //�þ߰Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MeleeAttackRange; //���ݻ�Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TraceRange; //�ִ� ���� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EAttributeKeyword MonsterAttribute;
public:
	//���� �Ӽ� ���µ��� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<EAttributeKeyword> MainAttributeDef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentHp;
};
	

