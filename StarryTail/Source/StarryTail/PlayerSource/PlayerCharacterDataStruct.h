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
	// 캐릭터 외 설정 값
	
	// 스프링암과 플레이어 간 기본 거리
	UPROPERTY(BlueprintReadWrite)
	float FollowCameraZPosition = 425;
	// 스프링암과 플레이어 간 최대 거리
	UPROPERTY(BlueprintReadWrite)
	float MaxFollowCameraZPosition = 550;
	// 스프링암과 플레이어 간 최소 거리
	UPROPERTY(BlueprintReadWrite)
	float MinFollowCameraZPosition = 120;

	UPROPERTY(BlueprintReadWrite)
	float MaxBattleCameraZPosition = 700;
	UPROPERTY(BlueprintReadWrite)
	float MaxRaidCameraZPosition = 1200;

	UPROPERTY(BlueprintReadWrite)
	float BattleCameraZPosition = 700;

	// 카메라 수평필드 오브 뷰
	UPROPERTY(BlueprintReadWrite)
	float FieldOfView = 75;
	// 카메라 지연 속도
	UPROPERTY(BlueprintReadWrite)
	float MaxCameraLagSpeed = 5.0f;
		
	// 마우스 휠 속도
	UPROPERTY(BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;
	// 마우스 감도
	UPROPERTY(BlueprintReadWrite)
	float EDPI = 1.0f;

public:	
	// 캐릭터 설정 값

	// 무적상태
	UPROPERTY(BlueprintReadWrite)
	bool IsInvincibility = false;
	// 무적상태
	UPROPERTY(BlueprintReadWrite)
	bool IsSkipMonsterAttack = false;
	
	//공격력
	UPROPERTY(BlueprintReadWrite)
	float Strength = 20;
	//불 스택 추가 공격력
	UPROPERTY(BlueprintReadWrite)
	float FireQuillStackDmg = 1;
	//쉴드
	UPROPERTY(BlueprintReadWrite)
	float Shield = 0;
	
	// 최대 체력
	UPROPERTY(BlueprintReadWrite)
	float MaxHP = 2000;
	// 체력
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float CurrentHP;

	// Run 최대 속도
	UPROPERTY(BlueprintReadWrite)
	float RunMaxSpeed = 540.0f;
	// Sprint 최대 속도
	UPROPERTY(BlueprintReadWrite)
	float SprintMaxSpeed = 720.0f;
	// 전기 스택 추가 이동속도
	UPROPERTY(BlueprintReadWrite)
	float ThunderQuillStackSpeed = 1;
	// 전기 스택 추가 이동속도
	UPROPERTY(BlueprintReadWrite)
	float WaterDeBuffSpeed = 1;
public:
	// 공격 관련 변수들
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
	// 캡슐 공격 사거리
	UPROPERTY(BlueprintReadOnly)
	float AttackRange = 50.0f;
	// 캡슐 공격 사거리 반지름
	UPROPERTY(BlueprintReadOnly)
	float AttackRadius = 50.0f;
	// 타겟 추적 선형보간 속도
	UPROPERTY(BlueprintReadOnly)
	float TargetFollowSpeed = 8.0f;
	// 카메라 타겟 추적 선형보간 속도
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