// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IreneFSM.h"

#include "PlayerCharacterDataStruct.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FPlayerCharacterDataStruct
{
	GENERATED_BODY()

public:
	// �ڵ忡�� �ǵ鿩 ����ϴ� ����� ���� �� ������ ������ �ʿ�
	
	// �������ϰ� �÷��̾� �� �⺻ �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 550;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 75;

public:	
	// �ΰ��ӿ��� ���� ������ ����� ���� �� ������ �ϸ� ����
	
	// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincibility = false;

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATK = 20;

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100;
	// �ִ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP = 100;
	// ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;
	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentMP;

	// �̵��ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 1.0f;

	// Run �ִ� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunMaxSpeed = 600.0f;
	// Sprint �ִ� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintMaxSpeed = 1200.0f;

	// ���콺 �� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;

	// ���콺 ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EDPI = 1.0f;

public:
	// ���� ���� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsAttacking = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool CanNextCombo = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsComboInputOn = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 CurrentCombo = 0;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 MaxCombo = 3;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRange = 200.0f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius = 50.0f;
};
