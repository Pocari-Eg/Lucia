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
	// 코드에서 건들여 줘야하는 값들로 수정 후 컴파일 무조건 필요
	
	// 스프링암과 플레이어 간 기본 거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FollowCameraZPosition = 550;

	// 카메라 수평필드 오브 뷰
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FieldofView = 75;

public:	
	// 인게임에서 수정 가능한 값들로 수정 후 컴파일 하면 좋음
	
	// 무적상태
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInvincibility = false;

	//공격력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ATK = 20;

	// 최대 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP = 100;
	// 최대 마나
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP = 100;
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
	float SprintMaxSpeed = 1200.0f;

	// 마우스 휠 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseWheelSpeed = 10.0f;

	// 마우스 감도
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EDPI = 1.0f;

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
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRange = 200.0f;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float AttackRadius = 50.0f;
};
