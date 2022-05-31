// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../StarryTail.h"

#include "IreneAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackStopCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnFootStepDelegate);
DECLARE_MULTICAST_DELEGATE(FOnRadialDelegate);

/**
 * 
 */
enum class EStateEnum: uint8;

UCLASS()
class STARRYTAIL_API UIreneAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	class AIreneCharacter* Irene;
	
protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsSprintState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsSprintStop;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EStateEnum IreneState;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FireAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WaterAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ThunderAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FireSkill1Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FireSkill2Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WaterSkillMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ThunderSkillMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EAttributeKeyword Attribute;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsHaveTargetMonster;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	AActor* TargetMonster;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int FireChargeCount;
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	
	UIreneAnimInstance();
	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlaySkillAttackMontage(const int AttackCount = 1);
	void NextToAttackMontageSection(const int32 NewSection);
	void JumpToAttackMontageSection(const int32 NewSection);
	
	void SetDeadAnim(const bool Value) { IsDead = Value; }
	void SetSprintStateAnim(const bool Value) { IsSprintState = Value; }
	void SetSprintStopAnim(const bool Value) { IsSprintStop = Value; }
	void SetIreneStateAnim(const EStateEnum Value) { IreneState = Value; }
	void SetAttribute(const EAttributeKeyword Value) { Attribute = Value; }
	void SetIsHaveTargetMonster(const bool Value) { IsHaveTargetMonster = Value; }
	void SetTargetMonster(AActor* Value) { TargetMonster = Value; }
	void SetFireChargeCount(const int Value) { FireChargeCount = Value; }

	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnAttackStopCheckDelegate OnAttackStopCheck;
	FOnFootStepDelegate OnFootStep;
	FOnRadialDelegate OnRadialBlur;
protected:

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck() const;
	UFUNCTION()
	void AnimNotify_NextAttackCheck() const;
	UFUNCTION()
	void AnimNotify_AttackStopCheck() const;
	UFUNCTION()
	void AnimNotify_MoveSkipCheck() const;
	UFUNCTION()
	void AnimNotify_DodgeJumpSkipCheck() const;
	UFUNCTION()
	void AnimNotify_FootStep() const;
	UFUNCTION()
	void AnimNotify_RadialBlur	() const;
	FName GetAttackMontageSectionName(const int32 Section);

public:
	int GetFireChargeCount()const { return FireChargeCount; }
};
