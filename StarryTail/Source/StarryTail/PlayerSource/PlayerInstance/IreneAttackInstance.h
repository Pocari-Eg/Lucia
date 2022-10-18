// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../../StarryTail.h"
#include "../PlayerCharacterDataStruct.h"

#include "IreneAttackInstance.generated.h"

UCLASS()
class STARRYTAIL_API UIreneAttackInstance : public UObject
{
	GENERATED_BODY()
public:
	// 타겟 몬스터 또는 오브젝트
	UPROPERTY()
	AActor* SwordTargetMonster;

	// 저스트 회피중인  몬스터
	UPROPERTY()
	AActor* PerfectDodgeMonster;
private:
	UPROPERTY()
	class AIreneCharacter* Irene;
	
	// 저스트 회피
	bool IsPerfectDodge = false;
	
	UPROPERTY()
	TArray<UParticleSystem*> BuffParticle;
	
	UPROPERTY()
	UDataTable* AttackDataTable;
	UPROPERTY()
	UDataTable* ElementDataTable;
	UPROPERTY()
	UDataTable* WeaponGaugeDataTable;
	UPROPERTY()
	UDataTable* WeaponSoulDataTable;

	// 진짜 공격 횟수
	int TrueAttackCount;

	// 피격이나 사망 전 공격 테이블 이름
	FString DamageBeforeTableName;
	
	// 스택 카운트 저장
	int StackCount;
	
	// 타켓 추적 유무
	bool bFollowTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetAlpha;
	// 보간을 위한 시작 위치
	FVector PlayerPosVec;
	// 보간을 위한 목표 위치
	FVector TargetPosVec;
	// 이동 전 위치
	FVector CurrentPosVec;
	// 이동 후 위치
	FVector NowPosVec;
	
	// 카메라 쉐이크 시간
	float CameraShakeTime;
	// 타켓 추적 유무
	bool bFollowCameraTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetCameraAlpha;
	// 보간을 위한 시작 위치
	FRotator CameraRot;
	// 보간을 위한 목표 위치
	FRotator TargetCameraRot;	
	
	// 후딜 중 이동 가능 타이밍 노티파이
	bool bMoveSkip;
	// 후딜 중 닷지나 점프 가능 타이밍 노티파이
	bool bDodgeJumpSkip;
	// 후딜 중 스킬 사용 가능 타이밍 노티파이
	bool bSkillSkip;
	// 스킬 사용 중 일반 공격 가능 타이밍 노티파이
	bool bSkillToAttack;
public:
	void Init(AIreneCharacter* Value);

private:
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	
public:
	// 검 공격 함수
	void AttackStartComboState();
	void AttackEndComboState();
	void AttackTimeEndState();
	void AttackCheck();
	void AttackStopCheck();
	void DoAttack();
	void SendDamage(bool bResult, TArray<FHitResult> MonsterList);
	
	FAttackDataTable* GetNameAtAttackDataTable(const FName Value) const { if (Value != FName("")) return (AttackDataTable->FindRow<FAttackDataTable>(Value, "")); return nullptr; }
	FElementDataTable* GetNameAtElementDataTable(const FName Value) const { if (Value != FName("")) return (ElementDataTable->FindRow<FElementDataTable>(Value, "")); return nullptr; }
	FWeaponGauge* GetNameAtWeaponGaugeDataTable(const FName Value) const { if (Value != FName("")) return (WeaponGaugeDataTable->FindRow<FWeaponGauge>(Value, "")); return nullptr; }
	FWeaponSoul* GetNameAtWeaponSoulDataTable() const { return WeaponSoulDataTable->FindRow<FWeaponSoul>(FName("Weapon_Soul"), "");}

#pragma region GetSet
	// 공격력 반환
	float GetATK()const;

	FName GetBasicAttackDataTableName();
	FName GetWeaponGaugeDataTableName();

	bool GetFollowTarget()const {return bFollowTarget;}
	float GetFollowTargetAlpha()const {return FollowTargetAlpha;}
	FVector GetPlayerPosVec()const {return PlayerPosVec;}
	FVector GetTargetPosVec()const {return TargetPosVec;}
	FVector GetCurrentPosVec()const {return CurrentPosVec;}
	FVector GetNowPosVec()const {return NowPosVec;}
	float GetCameraShakeTime()const {return CameraShakeTime;}
	bool GetCanMoveSkip()const{return bMoveSkip;}
	bool GetCanDodgeJumpSkip()const{return bDodgeJumpSkip;}
	bool GetCanSkillSkip()const{return bSkillSkip;}
	bool GetCanSkillToAttack()const{return bSkillToAttack;}
	bool GetIsPerfectDodge()const{return IsPerfectDodge;}

	void SetAttackState()const;
	void SetSkillState()const;
	void SetGauge(float Value);
	void SetFollowTarget(const bool Value){bFollowTarget = Value;}
	void SetFollowTargetAlpha(const float Value){FollowTargetAlpha = Value;}
	void SetPlayerPosVec(const FVector Value){PlayerPosVec = Value;}
	void SetTargetPosVec(const FVector Value){TargetPosVec = Value;}
	void SetCameraShakeTime(const float Value){CameraShakeTime = Value;}
	void SetCurrentPosVec(const FVector Value){CurrentPosVec = Value;}
	void SetNowPosVec(const FVector Value){NowPosVec = Value;}
	void SetCanMoveSkip(const bool Value){bMoveSkip = Value;}
	void SetCanDodgeJumpSkip(const bool Value){bDodgeJumpSkip = Value;}
	void SetCanSkillSkip(const bool Value){bSkillSkip = Value;}
	void SetCanSkillToAttack(const bool Value){bSkillToAttack = Value;}
	void SetIsPerfectDodge(const bool Value);
	void SetIsPerfectDodgeMonster(AActor* Monster) { PerfectDodgeMonster = Monster; }
	void SetTrueAttackCount(const int Value) { TrueAttackCount = Value; }
	void SetDamageBeforeTableName(const FString Value) {DamageBeforeTableName = Value;}
	void SetStackCount(const int Value) {StackCount = Value;}
#pragma endregion GetSet

private:
	UIreneAttackInstance();
};
