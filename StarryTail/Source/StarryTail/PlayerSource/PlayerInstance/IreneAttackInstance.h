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
	// 깃펜을 보낼 수 있는 몬스터 또는 오브젝트
	UPROPERTY()
	AActor* QuillTargetMonster;
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	EAttributeKeyword QuillAttribute;
	
	// 저스트 회피
	bool IsPerfectDodge = false;
	
	UPROPERTY()
	TArray<UParticleSystem*> BuffParticle;
	
	UPROPERTY()
	UDataTable* AttackDataTable;
	UPROPERTY()
	UDataTable* QuillDataTable;
	UPROPERTY()
	UDataTable* ChargeDataTable;
	UPROPERTY()
	UDataTable* ElementDataTable;

	// 깃펜 효과 타이머
	FTimerHandle FireQuillStackTimerHandle;
	FTimerHandle WaterQuillStackTimerHandle;
	FTimerHandle ThunderQuillStackTimerHandle;
	// 디버프 효과 타이머
	FTimerHandle FireDeBuffStackTimerHandle;
	FTimerHandle FireDeBuffTickTimerHandle;
	FTimerHandle WaterDeBuffStackTimerHandle;
	FTimerHandle ThunderDeBuffStackTimerHandle;
	FTimerHandle ThunderDeBuffTickTimerHandle;

	// 디버프 중첩 단계
	int FireDeBuffStack;
	int WaterDeBuffStack;
	int ThunderDeBuffStack;

	// 불속성 몬스터 고정 데미지
	float FireMonsterDamageAmount;
	// 전기 디버프 작동 시간
	float ThunderSustainTime;
	
	// 타켓 추적 유무
	bool bFollowTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetAlpha;
	// 보간을 위한 시작 위치
	FVector PlayerPosVec;
	// 보간을 위한 목표 위치
	FVector TargetPosVec;
	// 전기 스킬 이동 전 위치
	FVector CurrentPosVec;
	// 전기 스킬 이동 후 위치
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
	// 후딜 중 재공격 가능 타이밍 노티파이
	bool bReAttackSkip;
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

	// 깃펜 스택 함수
	void SetFireQuillStack(const int Value);
	void SetWaterQuillStack(const int Value);
	void SetThunderQuillStack(const int Value);
	void ResetFireQuillStack();
	void ResetWaterQuillStack();
	void ResetThunderQuillStack();

	// 디버프 스택 함수
	void SetFireDeBuffStack(const int Value, const float DamageAmount);
	void SetWaterDeBuffStack(const int Value);
	void SetThunderDeBuffStack(const int Value);
	void LoopFireDeBuff()const;
	void ResetFireDeBuffStack();
	void ResetWaterDeBuffStack();
	void ResetThunderDeBuffStack();
	void OverSustainTime();

	void SetAttackState()const;
	
	FAttackDataTable* GetNameAtAttackDataTable(const FName Value) const { if (Value != FName("")) return (AttackDataTable->FindRow<FAttackDataTable>(Value, "")); return nullptr; }
	FQuillDataTable* GetNameAtQuillDataTable(const FName Value) const { if (Value != FName("")) return (QuillDataTable->FindRow<FQuillDataTable>(Value, "")); return nullptr; }
	FChargeDataTable* GetNameAtChargeDataTable() const { return (ChargeDataTable->FindRow<FChargeDataTable>(FName("Charge"), "")); }
	FElementDataTable* GetNameAtElementDataTable(const FName Value) const { if (Value != FName("")) return (ElementDataTable->FindRow<FElementDataTable>(Value, "")); return nullptr; }

#pragma region GetSet
	//공격력 반환
	float GetATK()const;

	FName GetBasicAttackDataTableName();

	//속성 반환
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetQuillAttribute()const{return QuillAttribute;}
	bool GetFollowTarget()const {return bFollowTarget;}
	float GetFollowTargetAlpha()const {return FollowTargetAlpha;}
	FVector GetPlayerPosVec()const {return PlayerPosVec;}
	FVector GetTargetPosVec()const {return TargetPosVec;}
	FVector GetCurrentPosVec()const {return CurrentPosVec;}
	FVector GetNowPosVec()const {return NowPosVec;}
	float GetCameraShakeTime()const {return CameraShakeTime;}
	bool GetCanMoveSkip()const{return bMoveSkip;}
	bool GetCanDodgeJumpSkip()const{return bDodgeJumpSkip;}
	bool GetCanReAttackSkip()const{return bReAttackSkip;}
	FName GetAttributeToFormTimeDataTableName()const;
	int GetFireDeBuffStack()const{return FireDeBuffStack;}
	int GetWaterDeBuffStack()const{return WaterDeBuffStack;}
	int GetThunderDeBuffStack()const{return ThunderDeBuffStack;}
	float GetThunderSustainTime()const{return ThunderSustainTime;}
	bool GetIsPerfectDodge()const{return IsPerfectDodge;}
	
	void SetQuillAttribute(const EAttributeKeyword Value){QuillAttribute = Value;}
	void SetFollowTarget(const bool Value){bFollowTarget = Value;}
	void SetFollowTargetAlpha(const float Value){FollowTargetAlpha = Value;}
	void SetPlayerPosVec(const FVector Value){PlayerPosVec = Value;}
	void SetTargetPosVec(const FVector Value){TargetPosVec = Value;}
	void SetCameraShakeTime(const float Value){CameraShakeTime = Value;}
	void SetCurrentPosVec(const FVector Value){CurrentPosVec = Value;}
	void SetNowPosVec(const FVector Value){NowPosVec = Value;}
	void SetCanMoveSkip(const bool Value){bMoveSkip = Value;}
	void SetCanDodgeJumpSkip(const bool Value){bDodgeJumpSkip = Value;}
	void SetCanReAttackSkip(const bool Value){bReAttackSkip = Value;}
	void SetThunderSustainTime(const float Value){ThunderSustainTime = Value;}
	void SetIsPerfectDodge(const bool Value, const TArray<uint8> PerfectDodgeDir);
#pragma endregion GetSet

private:
	UIreneAttackInstance();
};
