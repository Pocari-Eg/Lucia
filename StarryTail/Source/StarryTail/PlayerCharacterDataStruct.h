// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IreneFSM.h"
#include "Engine/DataTable.h"

#include "PlayerCharacterDataStruct.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FPlayerCharacterDataStruct
{
	GENERATED_BODY()

public:
	// ĳ���� �� ���� ��
	
	// �������ϰ� �÷��̾� �� �⺻ �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 550;
	// �������ϰ� �÷��̾� �� �ִ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFollowCameraZPosition = 550;
	// �������ϰ� �÷��̾� �� �ּ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFollowCameraZPosition = 250;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraLagSpeed = 5.0f;

	// ���������Ŀ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpStartPower = 450;

	// ���콺 �� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;
	// ���콺 ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EDPI = 1.0f;

public:	
	// ĳ���� ���� ��

	// ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincibility = false;

	//���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 20;
	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defenses = 10;

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 2000;
	// �ִ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP = 1500;
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
	float SprintMaxSpeed = 900.0f;

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
	int32 MaxCombo = 5;
	// ĸ�� ���� ��Ÿ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRange = 100.0f;
	// ĸ�� ���� ��Ÿ� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius = 50.0f;
	// Ÿ�� ���� �������� �ӵ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float TargetFollowSpeed = 8.0f;
};

USTRUCT(BlueprintType)
struct FAttackDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Move_TYPE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Pre_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Charge_Gage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Charge_Time_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Charge_Time_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Charge_Time_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ATTACK_DAMAGE_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ATTACK_DAMAGE_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ATTACK_DAMAGE_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Distance_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Distance_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Distance_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Save_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int C_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Main_Keyword;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MANA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Key_Set;

};