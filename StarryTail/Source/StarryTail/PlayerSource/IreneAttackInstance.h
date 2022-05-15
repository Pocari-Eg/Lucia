// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../StarryTail.h"
#include "PlayerCharacterDataStruct.h"

#include "IreneAttackInstance.generated.h"

UCLASS()
class STARRYTAIL_API UIreneAttackInstance : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	// 타겟 몬스터 또는 오브젝트
	AActor* TargetMonster;
	
private:
	UPROPERTY()
	class AIreneCharacter* Irene;
	
	EAttributeKeyword Attribute;

	UPROPERTY()
	UDataTable* AttackDataTable;

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

	bool bUseMP;
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	void AttackStopCheck();
	void DoAttack();

	void SetAttackState()const;
	void SetSkillState()const;
	
	FAttackDataTable* GetNameAtAttackDataTable(const FName Value) const { if (Value != FName("")) return (AttackDataTable->FindRow<FAttackDataTable>(Value, "")); return nullptr; }

#pragma region GetSet
	//공격력 반환
	float GetATK()const;
	int GetAttackDirection();
	FName GetBasicAttackDataTableName();
	FName GetActionAttackDataTableName();

	//속성 반환
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetAttribute()const{return Attribute;}
	bool GetFollowTarget()const {return bFollowTarget;}
	float GetFollowTargetAlpha()const {return FollowTargetAlpha;}
	FVector GetPlayerPosVec()const {return PlayerPosVec;}
	FVector GetTargetPosVec()const {return TargetPosVec;}
	FVector GetCurrentPosVec()const {return CurrentPosVec;}
	FVector GetNowPosVec()const {return NowPosVec;}
	float GetCameraShakeTime()const {return CameraShakeTime;}
	bool GetUseMP()const {return bUseMP;}
	
	void SetAttribute(const EAttributeKeyword Value){Attribute = Value;}
	void SetFollowTarget(const bool Value){bFollowTarget = Value;}
	void SetFollowTargetAlpha(const float Value){FollowTargetAlpha = Value;}
	void SetPlayerPosVec(const FVector Value){PlayerPosVec = Value;}
	void SetTargetPosVec(const FVector Value){TargetPosVec = Value;}
	void SetCameraShakeTime(const float Value){CameraShakeTime = Value;}
	void SetUseMP(const bool Value){bUseMP = Value;}
	void SetCurrentPosVec(const FVector Value){CurrentPosVec = Value;}
	void SetNowPosVec(const FVector Value){NowPosVec = Value;}

#pragma endregion GetSet

private:
	UIreneAttackInstance();
};
