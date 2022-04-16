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
	// 캐릭터 외 설정 값
	
	// 스프링암과 플레이어 간 기본 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 550;
	// 스프링암과 플레이어 간 최대 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxFollowCameraZPosition = 550;
	// 스프링암과 플레이어 간 최소 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFollowCameraZPosition = 250;

	// 카메라 수평필드 오브 뷰
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxCameraLagSpeed = 5.0f;

	// 점프시작파워
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpStartPower = 450;

	// 마우스 휠 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;
	// 마우스 감도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EDPI = 1.0f;

public:	
	// 캐릭터 설정 값

	// 무적상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincibility = false;

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 20;
	//방어력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Defenses = 10;

	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 2000;
	// 최대 마나
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP = 1500;
	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHP;
	// 마나
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentMP;

	// 이동속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeed = 1.0f;

	// Run 최대 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunMaxSpeed = 600.0f;
	// Sprint 최대 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintMaxSpeed = 900.0f;

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
	int32 MaxCombo = 5;
	// 캡슐 공격 사거리
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRange = 100.0f;
	// 캡슐 공격 사거리 반지름
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius = 50.0f;
	// 타겟 추적 선형보간 속도
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