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
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

	//현재 회복 대기 시간
	float CurFireRecoverWaitTime;
	//현재 회복 시간
	float CurFireRecoverTime;
	//남은 회복량
	int RemainingFireRecovery;
	//타이머 핸들
	FTimerHandle FireRecoveryTimerHandle;
	FTimerHandle FireRecoveryWaitTimerHandle;
	bool IsConsecutiveFire;
	//현재 회복 대기 시간
	float CurWaterRecoverWaitTime;
	//현재 회복 시간
	float CurWaterRecoverTime;
	//남은 회복량
	int RemainingWaterRecovery;
	//타이머 핸들
	FTimerHandle WaterRecoveryTimerHandle;
	FTimerHandle WaterRecoveryWaitTimerHandle;
	bool IsConsecutiveWater;
	//현재 회복 대기 시간
	float CurElectricRecoverWaitTime;
	//현재 회복 시간
	float CurElectricRecoverTime;
	//남은 회복량
	int RemainingElectricRecovery;
	//타이머 핸들
	FTimerHandle ElectricRecoveryTimerHandle;
	FTimerHandle ElectricRecoveryWaitTimerHandle;
	bool IsConsecutiveElectric;

public:
	UPROPERTY()
	// 타겟 몬스터 또는 오브젝트
	AActor* TargetMonster;
	
	UPROPERTY(EditAnywhere)
	EAttributeKeyword Attribute;
	
	UPROPERTY()
	UDataTable* AttackDataTable;
	UPROPERTY()
	UDataTable* FormDataTable;
	
	// 폼 게이지 0 = Fire, 1 = Water, 2 = Electric
	UPROPERTY()
	TArray<float> FormGauge;
	
	// 타켓 추적 유무
	bool bFollowTarget;
	// 보간을 위한 수 0 ~ 1
	float FollowTargetAlpha;
	// 보간을 위한 시작 위치
	FVector PlayerPosVec;
	// 보간을 위한 목표 위치
	FVector TargetPosVec;

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
	float UseMP;	
private:
	UIreneAttackInstance();
	int GetAttackDirection();
	
	void FireRecoveringStart();
	void FireRecovering();
	void FireRecoveringCancel();
	bool IsFireFull();
	float GetFireRecoveryRatio();
	void WaterRecoveringStart();
	void WaterRecovering();
	void WaterRecoveringCancel();
	bool IsWaterFull();
	float GetWaterRecoveryRatio();
	void ElectricRecoveringStart();
	void ElectricRecovering();
	void ElectricRecoveringCancel();
	bool IsElectricFull();
	float GetElectricRecoveryRatio();
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();

	//공격력 반환
	float GetATK();
	//속성 반환
	UFUNCTION(BlueprintCallable)
	EAttributeKeyword GetAttribute();
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	void AttackStopCheck();
	void DoAttack();

	FAttackDataTable* GetNameAtAttackDataTable(const FName Value) const { if (Value != FName("")) return (AttackDataTable->FindRow<FAttackDataTable>(Value, "")); return nullptr; }
	FFormDataTable* GetNameAtFormDataTable(const FName Value) const { if (Value != FName("")) return (FormDataTable->FindRow<FFormDataTable>(Value, "")); return nullptr; }

	void FireRecoveryWaitStart();
	void FireRecoveryWaiting();
	void FireRecoveryWaitCancel();
	void WaterRecoveryWaitStart();
	void WaterRecoveryWaiting();
	void WaterRecoveryWaitCancel();
	void ElectricRecoveryWaitStart();
	void ElectricRecoveryWaiting();
	void ElectricRecoveryWaitCancel();
};
