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
public:
	// 움직임에 사용하는 키 0: 정지, 1: 걷기, 2: 달리기, 3: 걷기 예약키, 4: 달리기 예약키
	UPROPERTY()
	TArray<uint8> MoveKey;

	bool bLeftButtonPressed;
	bool bRightButtonPressed;
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	bool bNextAttack;
	bool bJumpAttack;
	bool bReAttack;
	
	FTimerHandle AttributeChangeFireTimer;
	FTimerHandle AttributeChangeWaterTimer;
	FTimerHandle AttributeChangeElectricTimer;

	// 추락중 구르기 시 빠르게 떨어지는 지 확인
	bool IsFallingRoll;

	// 공격 연속 입력 지연
	FTimerHandle AttackWaitHandle;
	// 창에서 검으로 변경
	FTimerHandle WeaponChangeWaitHandle;
	
	// 스킬 사용중
	bool bIsSkillOn;
	// 공격 중 스킬 사용
	bool bAttackUseSkill;
	// 2번째 검 스킬 사용
	bool CanUseSecondSwordSkill;
	// 전기 스킬 사용 가능
	bool bIsSpearSkill1On;
	// 최대 전기 스킬 횟수
	int MaxSpearSkill1Count;
	// 전기 스킬 횟수
	int SpearSkill1Count;
	
	// 공격 중 속성변경을 위한 변수
	EAttributeKeyword TempAttribute;
	//저스트 회피 방향
	UPROPERTY()
	TArray<uint8> PerfectDodgeDir;

	FTimerHandle DodgeInvincibilityTimerHandle;
	FTimerHandle PerfectDodgeTimerHandle;
	FTimerHandle PerfectDodgeInvincibilityTimerHandle;
	float SlowScale;
	
	bool bIsDialogOn;

#pragma region CoolTimeValue
private:

	float MaxSoulValue;
	float CurSoulValue;
	

	bool bIsThunderAttributeOn;

	// 검 스킬 최대 쿨타임
	float MaxSwordSkillCoolTime;
	// 검 스킬 쿨타임
	float SwordSkillCoolTime;
	// 검 스킬 종료 쿨타임
	FTimerHandle SwordSkillWaitHandle;
	// 검 2번 스킬 사용가능 시간
	FTimerHandle SwordSkill2WaitHandle;
	// 창 스킬 최대 쿨타임
	float MaxSpearSkill1CoolTime;
	// 창 스킬 쿨타임
	float SpearSkill1CoolTime;
	// 창 스킬 쿨타임
	FTimerHandle SpearSkill1WaitHandle;
	
	// 닷지 쿨타임
	FTimerHandle DodgeWaitHandle;
	
	float CoolTimeRate;
#pragma endregion CoolTimeValue
	
public:
	void Init(AIreneCharacter* Value);
	void Begin();
private:
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();

#pragma region Move
public:
	void MoveForward();
	void MoveRight();
	void MoveAuto(const float EndTimer = 1.0f)const;

	void MovePressedKey(const int Value);
	void MoveW(float Rate);
	void MoveA(float Rate);
	void MoveS(float Rate);
	void MoveD(float Rate);

	FVector GetMoveKeyToDirVector();
	int GetMoveKeyToDirNumber();
#pragma endregion Move

#pragma region OtherInput
public:
	// 카메라 회전 관련 함수
	void Turn(float Rate);
	void LookUp(float Rate);

	// 마우스 버튼 및 휠
	void LeftButton(float Rate);
	void RightButton(float Rate);
	void SpearRightButton();
	void SkillWait();
	void SpearSkill1Wait();
	void MouseWheel(float Rate);

	// 대쉬
	void DodgeKeyword();
	void PerfectDodge();
	bool CalcPerfectDodgeDir(FVector DodgeDirection);
	void PerfectDodgeStart();
	void PerfectDodgeTimeEnd();
	void PerfectDodgeAttackEnd();

	// 무기 변경
	void WeaponChangeKeyword();
	void WeaponChangeTimeOut();
	
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
#pragma endregion UIandStamina

#pragma region CheckStateChange
	bool CanRunState()const;
	bool CanAttackState()const;
	bool CanSkillState()const;
#pragma endregion CheckStateChange

#pragma region GetSet
public:
	bool GetFallingRoll()const{return IsFallingRoll;}
	bool GetIsDialogOn()const{return bIsDialogOn;}
	EAttributeKeyword GetTempAttribute()const{return TempAttribute;}
	float GetSlowScale()const{return SlowScale;}
	bool GetReAttack()const{return bReAttack;}
	bool GetAttackUseSkill()const{return bAttackUseSkill;}
	bool GetCanUseSecondSwordSkill()const{return CanUseSecondSwordSkill;}
	int GetSpearSkill1Count()const{return SpearSkill1Count;}

	void SetFallingRoll(const bool Value){IsFallingRoll = Value;}
	void SetStartMoveAutoTarget(const FVector SetPlayerPosVec, const FVector SetTargetPosVec)const;
	void SetStopMoveAutoTarget()const;
	void SetDialogState(const bool State) { bIsDialogOn = State; }
	void SetTempAttribute(const EAttributeKeyword Value){TempAttribute = Value;}
	void SetIsPerfectDodge(const TArray<uint8> Value) { PerfectDodgeDir = Value; }
	void SetNextAttack(const bool State) { bNextAttack = State; }
	void SetJumpAttack(const bool State) { bJumpAttack = State; }
	void SetReAttack(const bool State) { bReAttack = State; }
	void SetAttackUseSkill(const bool Value) { bAttackUseSkill = Value; }
	void SetCanUseSecondSwordSkill(const bool Value) { CanUseSecondSwordSkill = Value; }
#pragma endregion GetSet

};
