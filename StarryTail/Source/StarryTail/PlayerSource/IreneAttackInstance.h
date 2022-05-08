// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../StarryTail.h"
#include "PlayerCharacterDataStruct.h"

#include "IreneAttackInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnFormGaugeChangeDelegate);
UCLASS()
class STARRYTAIL_API UIreneAttackInstance : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class AIreneCharacter* Irene;

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
	UPROPERTY()
	UDataTable* FormTimeDataTable;
	
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

	FOnFormGaugeChangeDelegate FOnFireGaugeChange;
	FOnFormGaugeChangeDelegate FOnWaterGaugeChange;
	FOnFormGaugeChangeDelegate FOnElectricGaugeChange;
private:
	UIreneAttackInstance();
	int GetAttackDirection();
	
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
	FFormTimeDataTable* GetNameAtFormTimeDataTable(const FName Value) const { if (Value != FName("")) return (FormTimeDataTable->FindRow<FFormTimeDataTable>(Value, "")); return nullptr; }
};
