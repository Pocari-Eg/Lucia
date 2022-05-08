﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IreneInputInstance.generated.h"

enum class  EAttributeKeyword :uint8;

UCLASS()
class STARRYTAIL_API UIreneInputInstance : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	FTimerHandle FireStartTimer;
	FTimerHandle WaterStartTimer;
	FTimerHandle ElectricStartTimer;
	
public:
	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기, 3: 걷기 예약키, 4: 달리기 예약키
	UPROPERTY()
	TArray<uint8> MoveKey;

	// 구르기 같은 자동이동 방향
	FVector MoveAutoDirection;
	// 자동이동용 핸들
	FTimerHandle MoveAutoWaitHandle;
	// 추락중 구르기 시 빠르게 떨어지는 지 확인
	bool IsFallingRoll;

	// 공격 연속 입력 지연
	FTimerHandle AttackWaitHandle;

	// 차징 중인지
	bool IsCharging;
	// 차징 시간
	float ChargingTime;

	// 점프 중력 그래프용 시작 타이밍
	bool bStartJump;
	// 점프 중력 그래프용 시간
	float JumpingTime;

	bool bUseLeftButton;
	bool bUseRightButton;

	float StaminaGauge;
	FTimerHandle StaminaWaitHandle;
	float StartWaterDodgeStamina;
private:
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	void ChangeForm(EAttributeKeyword Value);

#pragma region Move
	void MoveForward();
	void MoveRight();
	void MoveStop();
	void MoveAuto();

	void StartJump();
	void StopJump();

	void MovePressedW();
	void MovePressedA();
	void MovePressedS();
	void MovePressedD();
	void MoveDoubleClickW();
	void MoveDoubleClickA();
	void MoveDoubleClickS();
	void MoveDoubleClickD();
	void MoveReleasedW();
	void MoveReleasedA();
	void MoveReleasedS();
	void MoveReleasedD();
#pragma endregion Move

#pragma region Other
	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 버튼 및 휠
	void LeftButton(float Rate);
	void RightButtonPressed();
	void RightButtonReleased();
	void MouseWheel(float Rate);
	void RightButton(float Rate);

	// 메인키워드 속성변경
	void MainKeyword();
	void FireKeywordReleased();
	void WaterKeywordReleased();
	void ElectricKeywordReleased();
	
	// 대쉬
	void DodgeKeyword();
	void WaterDodgeKeyword(float Rate);
	
	// 마우스 커서 활성화
	void MouseCursorKeyword();

	// Pause위젯 on
	void PauseWidgetOn();

	void RecoveryStaminaGauge(float DeltaTime);
	bool StaminaGaugeIsFull()const;
#pragma endregion Other
};
