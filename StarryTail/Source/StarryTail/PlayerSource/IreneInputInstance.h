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
	bool bRightButtonPressed;
	bool bUseLeftButton;
	bool bUseRightButton;
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	FTimerHandle FireStartTimer;
	FTimerHandle WaterStartTimer;
	FTimerHandle ElectricStartTimer;

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
	
	// 차징 중인지
	bool IsCharging;
	// 차징 시간
	float ChargingTime;

	// 점프 중력 그래프용 시작 타이밍
	bool bStartJump;
	// 점프 중력 그래프용 시간
	float JumpingTime;

	// 스테미나 관련
	FTimerHandle StaminaWaitHandle;
	float StartWaterDodgeStamina;	

	bool bUseDodgeKey;
	bool bUseWaterDodge;

	// 닷지 쿨타임
	FTimerHandle DodgeWaitHandle;

	// 번개 닷지 관련
	FTimerHandle ThunderDodgeWaitHandle;
	
	// 스킬
	FTimerHandle FireSkillWaitHandle;
	FTimerHandle WaterSkillWaitHandle;
	FTimerHandle ThunderSkillWaitHandle;
	
	// 번개 스킬 갯수
	int ThunderSkillCount;
	int MaxThunderSkillCount;

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
	bool bIsFireAttributeOn;
	bool bIsWaterAttributeOn;
	bool bIsThunderAttributeOn;

	float FireSkillCoolTime;
	float MaxFireSkillCoolTime;

	float WaterSkillCoolTime;
	float MaxWaterSkillCoolTime;

	float ThunderSkillCoolTime;
	float MaxThunderSkillCoolTime;

	float FireQuillCoolTime;
	float MaxFireQuillCoolTime;
	float WaterQuillCoolTime;
	float MaxWaterQuillCoolTime;
	float ThunderQuillCoolTime;
	float MaxThunderQuillCoolTime;
	
	bool bIsFireSkillOn;
	bool bIsWaterSkillOn;
	bool bIsThunderSkillOn;
	
	bool bIsFireQuillOn;
	bool bIsWaterQuillOn;
	bool bIsThunderQuillOn;
	
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
	void RightButtonReleased();
	void MouseWheel(float Rate);

	// 메인키워드 속성변경
	void AttributeKeywordReleased(const EAttributeKeyword Attribute);
	void FireKeywordReleased();
	void WaterKeywordReleased();
	void ElectricKeywordReleased();
	
	// 대쉬
	void DodgeKeyword();
	void WaterDodgeKeyword(float Rate);	
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
	bool CanJumpState()const;
	bool CanRunState()const;
	bool CanAttackState()const;
#pragma endregion CheckStateChange

#pragma region GetSet
public:
	bool GetStartJump()const{return bStartJump;}
	float GetJumpingTime()const{return JumpingTime;}
	bool GetFallingRoll()const{return IsFallingRoll;}
	bool GetCharging()const{return IsCharging;}
	int GetThunderSkillCount()const{return ThunderSkillCount;}
	int GetFireQuillCount()const{return FireQuillCount;}
	int GetWaterQuillCount()const{return WaterQuillCount;}
	int GetThunderQuillCount()const{return ThunderQuillCount;}
	bool GetUseDodgeKey()const{return bUseDodgeKey;}
	bool GetFireSkillOn()const{return bIsFireSkillOn;}
	bool GetWaterSkillOn()const{return bIsWaterSkillOn;}
	bool GetThunderSkillOn()const{return bIsThunderSkillOn;}
	bool GetIsDialogOn()const{return bIsDialogOn;}
	
	void SetStartJump(const bool Value){bStartJump = Value;}
	void SetJumpingTime(const float Value){JumpingTime = Value;}
	void SetFallingRoll(const bool Value){IsFallingRoll = Value;}
	void SetDeltaTimeChargingTime(const float DeltaTime){ChargingTime += DeltaTime;}
	void SetStartMoveAutoTarget(const FVector SetPlayerPosVec, const FVector SetTargetPosVec)const;
	void SetStopMoveAutoTarget()const;
	void SetThunderSkillCount(const int Value) { ThunderSkillCount = Value; }
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

	void FireSkillWait();
	void WaterSkillWait();
	void ThunderSkillWait();

	void FireQuillWait();
	void WaterQuillWait();
	void ThunderQuillWait();
#pragma endregion CoolTimeFunction
};
