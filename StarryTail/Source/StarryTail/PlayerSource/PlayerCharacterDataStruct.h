// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	float FollowCameraZPosition = 425;
	// �������ϰ� �÷��̾� �� �ִ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFollowCameraZPosition = 550;
	// �������ϰ� �÷��̾� �� �ּ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFollowCameraZPosition = 120;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxBattleCameraZPosition = 700;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRaidCameraZPosition = 1200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BattleCameraZPosition = 700;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float FieldOfView = 75;
	// ī�޶� ���� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraLagSpeed = 5.0f;

	// ���������Ŀ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpStartPower = 550;
	// ���������Ŀ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpDrag = 1.2f;
	
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
	// �ִ� ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 150;
	// ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;
	// ���׹̳�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentStamina;

	// Run �ִ� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunMaxSpeed = 540.0f;
	// Sprint �ִ� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintMaxSpeed = 720.0f;

	// ���� �뽬 ���� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThunderDodgeTime = 1.0f;
	// ���� �뽬 �ӷ� �ӽð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FirstThunderDodgeSpeed = 800000.0f;
	// ���� �뽬 �ӷ� �ӽð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DoubleThunderDodgeSpeed = 1500000.0f;
	
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
	// ĸ�� ���� ��Ÿ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRange = 50.0f;
	// ĸ�� ���� ��Ÿ� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius = 50.0f;
	// Ÿ�� ���� �������� �ӵ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float TargetFollowSpeed = 8.0f;
	// ī�޶� Ÿ�� ���� �������� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetCameraFollowSpeed = 3.0f;

public:
	// ��Ÿ ������
	// SPȸ�� �ӵ�
	UPROPERTY()
	float Recovery_Speed = 7.5f;
	// SP���� �ӵ�
	UPROPERTY()
	float Decrease_Speed = 50.0f;
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
	int Attack_Power;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Pre_Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Charge_Gauge;
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
	int Form;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Key_Set;
};
USTRUCT(BlueprintType)
struct FFormTimeDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Form_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Form_C_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Target_Collision;
};

USTRUCT(Atomic, BlueprintType)
struct FPlayerRecoveryDataStruct
{
  GENERATED_BODY()  
public:
	//
	UPROPERTY(EditAnywhere,Category="HP_Recovery")
	int Amount;
	UPROPERTY(EditAnywhere, Category = "HP_Recovery")
	int Speed;
	UPROPERTY(EditAnywhere, Category = "HP_Recovery")
	int Time;
	UPROPERTY(EditAnywhere, Category = "HP_Recovery")
	int HP_Re_Time;
	UPROPERTY(VisibleAnywhere, Category = "HP_Recovery")
	bool bIsRecovering;			
};