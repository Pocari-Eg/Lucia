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
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	UPROPERTY()
	AActor* BreakAttackSpirit;
	bool bCameraStop;
	
	bool bNextAttack;
	bool bJumpAttack;
	bool bReAttack;

	// 정령 상태 지속 시간 넘김
	FTimerHandle SpiritTimeDamageOverTimer;
	FTimerHandle SpiritTimeStunOverTimer;

	// 브레이킹어택 카메라 정지 시간
	FTimerHandle BreakAttackCameraStopTimeTimer;
	// 브레이킹어택 정령 지속 시간
	FTimerHandle BreakAttackSpiritTimeTimer;
	// 브레이킹어택 애니메이션 시간
	FTimerHandle BreakAttackAnimTimeTimer;
	
	// 추락중 구르기 시 빠르게 떨어지는 지 확인
	bool IsFallingRoll;
	// 스턴 상태인지 확인
	bool bIsStun;
	
	// 회피 사용 가능
	bool bIsDodgeOn;
	// 최대 회피 횟수
	int MaxDodgeCount;
	// 회피 횟수
	int DodgeCount;
	// 회피 중 회피 사용 가능
	bool bIsDodgeToDodge;
	
	// 공격 연속 입력 지연
	FTimerHandle AttackWaitHandle;
	// 검에서 창으로 변경 이후 시간 지나서 디버프 발동
	FTimerHandle WeaponChangeWaitHandle;
	// 검에서 창으로 변경 이후 강제 검으로 변경
	FTimerHandle WeaponChangeMaxWaitHandle;

	// 스킬 사용중
	bool bIsSkillOn;
	// 공격 중 스킬 사용
	bool bAttackUseSkill;
	// 공격 중 스킬 사용 후 다음 공격 해야하는 단계
	int AttackUseSkillNextCount;
	// 2번째 검 스킬 사용
	bool CanUseSecondSwordSkill;

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
	// 검 스킬 종료 시 발동
	FTimerHandle SwordSkillEndWaitHandle;
	// 검 스킬 사용 가능 쿨타임
	FTimerHandle SwordSkillWaitHandle;
	// 검 2번 스킬 사용가능 시간
	FTimerHandle SwordSkill2WaitHandle;
	// 검 2번 스킬 사용가능 시간
	float CanSwordSkill2Time;
	// 공격 중 스킬 사용 후 다음 공격 해야하는 단계 사용 가능 시간
	FTimerHandle AttackUseSkillNextCountWaitHandle;
	
	// 회피 입력 쿨타임
	FTimerHandle DodgeInputWaitHandle;

	// 회피 회복 최대 쿨타임
	float MaxDodgeCoolTime;
	// 회피 회복 쿨타임
	float DodgeCoolTime;
	// 회피 회복 쿨타임
	FTimerHandle DodgeWaitHandle;

	// 잔상 소환 딜레이
	FTimerHandle SpiritSpawnWaitHandle;
	// 잔상 소환 딜레이 쿨타임
	float SpiritSpawnCoolTime;
	
	bool bSkillCameraMove;
	float SkillCameraPlayTime;
	float SkillCameraEndPlayTime;
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
	void NonSpiritSkill();
	void SpiritSkill();
	void SpawnSpirit();
	void SkillWait();
	void SwordSkillEndWait();

	void SkillCameraMoveStart();
	void SkillCameraMoveLoop(float DeltaTime);
	void SkillCameraMoveEnd(float DeltaTime);

	void MouseWheel(float Rate);

	// 대쉬
	void DodgeKeyword();
	void PerfectDodge();
	void PerfectDodgeStart();
	void PerfectDodgeTimeEnd();
	void PerfectDodgeAttackEnd();
	void RecoveryDodge();
	void RecoveryDodgeWait();

	// 스탠스 변경
	void SpiritChangeKeyword();
	void SpiritChangeTimeOver();
	void SpiritChangeMaxTime();
	void SpiritTimeOverDeBuff();

	// 브레이킹어택
	void BreakAttackKeyword();
	// 브레이킹어택 종료
	void BreakAttackEnd();
	
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
	float GetSlowScale()const{return SlowScale;}
	bool GetReAttack()const{return bReAttack;}
	bool GetAttackUseSkill()const{return bAttackUseSkill;}
	bool GetCanUseSecondSwordSkill()const{return CanUseSecondSwordSkill;}
	bool GetCameraStop()const{return bCameraStop;}
	
	void SetFallingRoll(const bool Value){IsFallingRoll = Value;}
	void SetStartMoveAutoTarget(const FVector SetPlayerPosVec, const FVector SetTargetPosVec)const;
	void SetStopMoveAutoTarget()const;
	void SetDialogState(const bool State) { bIsDialogOn = State; }
	void SetNextAttack(const bool State) { bNextAttack = State; }
	void SetJumpAttack(const bool State) { bJumpAttack = State; }
	void SetReAttack(const bool State) { bReAttack = State; }
	void SetAttackUseSkill(const bool Value) { bAttackUseSkill = Value; }
	void SetCanUseSecondSwordSkill(const bool Value) { CanUseSecondSwordSkill = Value; }
	void SetIsDodgeToDodge(const bool Value) {bIsDodgeToDodge = Value;}
#pragma endregion GetSet

};
