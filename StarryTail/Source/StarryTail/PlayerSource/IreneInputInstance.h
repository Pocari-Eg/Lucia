// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IreneInputInstance.generated.h"

enum class  EAttributeKeyword :uint8;

UCLASS()
class STARRYTAIL_API UIreneInputInstance : public UObject
{
	GENERATED_BODY()
public:
	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기, 3: 걷기 예약키, 4: 달리기 예약키
	UPROPERTY()
	TArray<uint8> MoveKey;

	bool bLeftButtonPressed;
	
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	FTimerHandle AttributeChangeFireTimer;
	FTimerHandle AttributeChangeWaterTimer;
	FTimerHandle AttributeChangeElectricTimer;

	// 속성 변경 시 사용되는 쿨타임
	float FireMaxCoolTime;
	float FireCurCoolTime;
	float WaterMaxCoolTime;
	float WaterCurCoolTime;
	float ThunderMaxCoolTime;
	float ThunderCurCoolTime;	

	// 추락중 구르기 시 빠르게 떨어지는 지 확인
	bool IsFallingRoll;

	// 공격 연속 입력 지연
	FTimerHandle AttackWaitHandle;

	// 스테미나 관련
	FTimerHandle StaminaWaitHandle;
	float StartWaterDodgeStamina;	
	
	// 닷지 쿨타임
	FTimerHandle DodgeWaitHandle;
	
	// 깃펜 갯수
	int FireQuillCount;
	int MaxFireQuillCount;
	int WaterQuillCount;
	int MaxWaterQuillCount;
	int ThunderQuillCount;
	int MaxThunderQuillCount;

	FTimerHandle FireQuillWaitHandle;
	FTimerHandle WaterQuillWaitHandle;
	FTimerHandle ThunderQuillWaitHandle;
	
	bool bIsDialogOn;
#pragma region CoolTimeValue
private:
	// 검 속성
	bool bIsFireAttributeOn;
	bool bIsWaterAttributeOn;
	bool bIsThunderAttributeOn;

	// 깃펜 속성, UI에서 사용
	bool bIsFireQuillOn;
	bool bIsWaterQuillOn;
	bool bIsThunderQuillOn;
	
	// 깃펜 사용 시 사용되는 쿨타임, UI에서 사용
	float FireQuillCurCoolTime;
	float FireQuillMaxCoolTime;
	float WaterQuillCurCoolTime;
	float WaterQuillMaxCoolTime;
	float ThunderQuillCurCoolTime;
	float ThunderQuillMaxCoolTime;
	
	float CoolTimeRate;
#pragma endregion CoolTimeValue
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	void Begin();
	void ChangeForm(const EAttributeKeyword Value);

#pragma region Move
	void MoveForward();
	void MoveRight();
	void MoveAuto(const float EndTimer = 1.0f)const;

	void MovePressedKey(const int Value);
	void MoveW(float Rate);
	void MoveA(float Rate);
	void MoveS(float Rate);
	void MoveD(float Rate);

	FVector GetMoveKeyToDirVector();
#pragma endregion Move

#pragma region OtherInput
	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 버튼 및 휠
	void LeftButton(float Rate);
	void RightButtonPressed();
	void MouseWheel(float Rate);

	// 메인키워드 속성변경
	void AttributeKeywordReleased(const EAttributeKeyword Attribute);
	void FireKeywordReleased();
	void WaterKeywordReleased();
	void ElectricKeywordReleased();
	void QuillAttributeChangeReleased();

	// 대쉬
	void DodgeKeyword();
	
	// 액션 
	void DialogAction();
	void DialogSkip();
#pragma endregion OtherInput

#pragma region UIandStamina
	// 마우스 커서 활성화
	void MouseCursorKeyword();

	// Pause위젯 on
	public:
	UFUNCTION(BluePrintcallable)
	void PauseWidgetOn();

	void RecoveryStaminaGauge(const float DeltaTime)const;
	bool StaminaGaugeIsFull()const;
#pragma endregion UIandStamina

#pragma region CheckStateChange
	bool CanRunState()const;
	bool CanAttackState()const;
#pragma endregion CheckStateChange

#pragma region GetSet
public:
	bool GetFallingRoll()const{return IsFallingRoll;}
	int GetFireQuillCount()const{return FireQuillCount;}
	int GetWaterQuillCount()const{return WaterQuillCount;}
	int GetThunderQuillCount()const{return ThunderQuillCount;}
	bool GetIsDialogOn()const{return bIsDialogOn;}
	
	void SetFallingRoll(const bool Value){IsFallingRoll = Value;}
	void SetStartMoveAutoTarget(const FVector SetPlayerPosVec, const FVector SetTargetPosVec)const;
	void SetStopMoveAutoTarget()const;
	void SetFireQuillCount(const int Value) { FireQuillCount = Value; }
	void SetWaterQuillCount(const int Value) { WaterQuillCount = Value; }
	void SetThunderQuillCount(const int Value) { ThunderQuillCount = Value; }
	void SetDialogState(const bool State) { bIsDialogOn = State; }
#pragma endregion GetSet	

#pragma region CoolTimeFunction
private:
	void FireCoolTime();
	void WaterCoolTime();
	void ThunderCoolTime();

	void FireQuillWait();
	void WaterQuillWait();
	void ThunderQuillWait();
#pragma endregion CoolTimeFunction
};
