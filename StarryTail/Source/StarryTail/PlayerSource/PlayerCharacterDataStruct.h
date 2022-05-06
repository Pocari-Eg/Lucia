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
	float FollowCameraZPosition = 550;
	// �������ϰ� �÷��̾� �� �ִ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFollowCameraZPosition = 550;
	// �������ϰ� �÷��̾� �� �ּ� �Ÿ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFollowCameraZPosition = 250;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float FieldOfView = 75;
	// ī�޶� ���� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraLagSpeed = 5.0f;

	// ���������Ŀ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpStartPower = 450;
	// ���������Ŀ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpDrag = 4;
	
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
	float AttackRange = 200.0f;
	// ĸ�� ���� ��Ÿ� ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius = 50.0f;
	// Ÿ�� ���� �������� �ӵ�
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float TargetFollowSpeed = 8.0f;
	// ī�޶� Ÿ�� ���� �������� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TargetCameraFollowSpeed = 3.0f;
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
	int Form;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Gauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Key_Set;
};
USTRUCT(BlueprintType)
struct FFormDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Form_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int F_Gauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Gauge_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Gauge_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Gauge_Recovery;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hit_Gauge_Re;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Open_Gauge;
};
USTRUCT(BlueprintType)
struct FFormTimeDataTable : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Form_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int F_Gauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Recovery_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Decrease_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hit_Gauge_Re;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Gauge_C_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Open_Gauge;
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
USTRUCT(Atomic, BlueprintType)
struct FPlayerFireRecoveryDataStruct
{
	GENERATED_BODY()  
public:
	//
	UPROPERTY(EditAnywhere,Category="Form_Recovery")
	int Amount;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	float Time;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	int Fire_Re_Time;
	UPROPERTY(VisibleAnywhere, Category = "Form_Recovery")
	bool bIsRecovering;			
};
USTRUCT(Atomic, BlueprintType)
struct FPlayerWaterRecoveryDataStruct
{
	GENERATED_BODY()  
public:
	//
	UPROPERTY(EditAnywhere,Category="Form_Recovery")
	int Amount;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	float Time;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	int Water_Re_Time;
	UPROPERTY(VisibleAnywhere, Category = "Form_Recovery")
	bool bIsRecovering;			
};
USTRUCT(Atomic, BlueprintType)
struct FPlayerElectricRecoveryDataStruct
{
	GENERATED_BODY()  
public:
	//
	UPROPERTY(EditAnywhere,Category="Form_Recovery")
	int Amount;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	float Time;
	UPROPERTY(EditAnywhere, Category = "Form_Recovery")
	int Electric_Re_Time;
	UPROPERTY(VisibleAnywhere, Category = "Form_Recovery")
	bool bIsRecovering;			
};