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
	
	// �������ϰ� �����̾� �� �⺻ �Ÿ�
	UPROPERTY(BlueprintReadWrite)
	float FollowCameraZPosition = 425;
	// �������ϰ� �÷��̾� �� �ִ� �Ÿ�
	UPROPERTY(BlueprintReadWrite)
	float MaxFollowCameraZPosition = 550;
	// �������ϰ� �÷��̾� �� �ּ� �Ÿ�
	UPROPERTY(BlueprintReadWrite)
	float MinFollowCameraZPosition = 120;

	UPROPERTY(BlueprintReadWrite)
	float MaxBattleCameraZPosition = 700;
	UPROPERTY(BlueprintReadWrite)
	float MaxRaidCameraZPosition = 1200;

	UPROPERTY(BlueprintReadWrite)
	float BattleCameraZPosition = 700;

	// ī�޶� �����ʵ� ���� ��
	UPROPERTY(BlueprintReadWrite)
	float FieldOfView = 80;
	// ī�޶� ���� �ӵ�
	UPROPERTY(BlueprintReadWrite)
	float MaxCameraLagSpeed = 5.0f;
		
	// ���콺 �� �ӵ�
	UPROPERTY(BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;
	// ���콺 ����
	UPROPERTY(BlueprintReadWrite)
	float EDPI = 1.0f;

public:	
	// ĳ���� ���� ��

	// ��������
	UPROPERTY(BlueprintReadWrite)
	bool IsInvincibility = false;
	// ��������
	UPROPERTY(BlueprintReadWrite)
	bool IsSkipMonsterAttack = false;
	
	// ���ݷ�
	UPROPERTY(BlueprintReadWrite)
	float Strength = 20;
	
	// �ִ� ü��
	UPROPERTY(BlueprintReadWrite)
	float MaxHP = 2000;
	// ü��
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentHP;
	// �ִ� ����
	UPROPERTY(BlueprintReadWrite)
	float MaxShield = 300;
	// ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentShield;
	// �ִ� ������ - �뽬
	UPROPERTY(BlueprintReadWrite)
	float MaxScrollEnergy = 100;
	// ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentEnergy;
	// �ִ� ������ - ���⺯��
	UPROPERTY(BlueprintReadWrite)
	float MaxGauge = 100;
	// ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentGauge;
	// �ִ� ������ - �ñر�
	UPROPERTY(BlueprintReadWrite)
	float MaxUltimateAttackGauge = 100;
	// ������
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentUltimateAttackGauge;
	
	// Run �ִ� �ӵ�
	UPROPERTY(BlueprintReadWrite)
	float RunMaxSpeed = 540.0f;
	// Sprint �ִ� �ӵ�
	UPROPERTY(BlueprintReadWrite)
	float SprintMaxSpeed = 720.0f;
	// ���� ����� �̵��ӵ�
	UPROPERTY(BlueprintReadWrite)
	float WaterDeBuffSpeed = 1;
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
	UPROPERTY(BlueprintReadOnly)
	float AttackRange = 50.0f;
	// ĸ�� ���� ��Ÿ� ������
	UPROPERTY(BlueprintReadOnly)
	float AttackRadius = 50.0f;
	// Ÿ�� ���� �������� �ӵ�
	UPROPERTY(BlueprintReadOnly)
	float TargetFollowSpeed = 8.0f;
	// ī�޶� Ÿ�� ���� �������� �ӵ�
	UPROPERTY(BlueprintReadOnly)
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
	int Attack_Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ATTACK_DAMAGE_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ATTACK_DAMAGE_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Distance_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Attack_Distance_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Stack_Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float C_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Key_Set;
};
USTRUCT(BlueprintType)
struct FElementDataTable : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Ele_Type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Ele_C_Time;
};
USTRUCT(BlueprintType)
struct FWeaponGauge : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Get_W_Gauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Get_B_Next;
};
USTRUCT(BlueprintType)
struct FWeaponSoul : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Move_Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Get_Distance_Gauge;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Get_Ultimate_Guage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Get_MaxUltimate_Guage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Drop_Distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Drop_Speed;
};
USTRUCT(Atomic, BlueprintType)
struct FPlayerRecoveryDataStruct
{
  GENERATED_BODY()  
public:
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