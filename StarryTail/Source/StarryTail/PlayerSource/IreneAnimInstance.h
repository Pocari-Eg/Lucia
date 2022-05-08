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
/**
 * 
 */
enum class EStateEnum: uint8;

UCLASS()
class STARRYTAIL_API UIreneAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

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
	UAnimMontage* AttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* EffectAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EAttributeKeyword Attribute;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsHaveTargetMonster;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	FVector TargetMonster;
    	
public:
	UIreneAnimInstance();
	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlayEffectAttackMontage();
	void JumpToAttackMontageSection(const int32 NewSection);
	void JumpToEffectAttackMontageSection(const int32 NewSection);
	
	void SetDeadAnim(const bool Value) { IsDead = Value; }
	void SetSprintStateAnim(const bool Value) { IsSprintState = Value; }
	void SetSprintStopAnim(const bool Value) { IsSprintStop = Value; }
	void SetIreneStateAnim(const EStateEnum Value) { IreneState = Value; }
	void SetAttribute(const EAttributeKeyword Value) { Attribute = Value; }
	void SetIsHaveTargetMonster(const bool Value) { IsHaveTargetMonster = Value; }
	void SetTargetMonster(const FVector Value) { TargetMonster = Value; }
	
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnAttackStopCheckDelegate OnAttackStopCheck;
	FOnFootStepDelegate OnFootStep;
protected:

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck() const;
	UFUNCTION()
	void AnimNotify_NextAttackCheck() const;
	UFUNCTION()
	void AnimNotify_AttackStopCheck() const;
	UFUNCTION()
	void AnimNotify_FootStep() const;
	FName GetAttackMontageSectionName(const int32 Section);
};
