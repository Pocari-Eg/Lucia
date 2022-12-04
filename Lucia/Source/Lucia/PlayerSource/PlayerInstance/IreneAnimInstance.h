// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IreneUIManager.h"
#include "../../Lucia.h"

#include "IreneAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackStopCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnFootStepDelegate);
DECLARE_MULTICAST_DELEGATE(FOnRadialDelegate);

/**
 * 
 */
enum class EStateEnum: uint8;

UCLASS()
class LUCIA_API UIreneAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnAttackStopCheckDelegate OnAttackStopCheck;
	FOnFootStepDelegate OnFootStep;
	FOnRadialDelegate OnRadialBlur;
private:
	UPROPERTY()
	AIreneCharacter* Irene;
	
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
	bool IsStartBreakAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsMoveStopBreakAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDoAttackBreakAttack;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EStateEnum IreneState;		
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsHaveTargetMonster;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	AActor* TargetMonster;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int DodgeDir;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bSpiritStart;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float SprintPlayRate;
	


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SwordAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritAttackMontage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SwordSkill1Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SwordSkill2Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkill1Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkill2Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkill3Montage;

public:
	void Init(AIreneCharacter* Value);

private:
	UIreneAnimInstance();

	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
public:
	void PlayAttackMontage();
	void PlaySkillAttackMontage(const int AttackCount = 1);
	void NextToAttackMontageSection(const int32 NewSection);
	void JumpToAttackMontageSection(const int32 NewSection);
	
	void SetDeadAnim(const bool Value) { IsDead = Value; }
	void SetSprintStateAnim(const bool Value) { IsSprintState = Value; }
	void SetSprintStopAnim(const bool Value) { IsSprintStop = Value; }
	void SetIsStartBreakAttack(const bool Value) { IsStartBreakAttack = Value; }
	void SetIsMoveStopBreakAttack(const bool Value) { IsMoveStopBreakAttack = Value; }
	void SetIsDoAttackBreakAttack(const bool Value) { IsDoAttackBreakAttack = Value; }
	void SetIreneStateAnim(const EStateEnum Value) { IreneState = Value; }
	void SetIsHaveTargetMonster(const bool Value) { IsHaveTargetMonster = Value; }
	void SetTargetMonster(AActor* Value) { TargetMonster = Value; }
	void SetDodgeDir(const int Value) { DodgeDir = Value; }
	void SetSpiritStart(const bool Value) { bSpiritStart = Value; }
	void SetSprintPlayRate(const float Value) { SprintPlayRate = Value; }

	bool GetIsinAir()const{return IsInAir;}
	int GetDodgeDir()const{return DodgeDir;}
	bool GetIsMoveStopBreakAttack()const{return IsMoveStopBreakAttack;}

public:
	UFUNCTION(BlueprintCallable)
	void CallCreateTail();
	UFUNCTION(BlueprintImplementableEvent)
	void KnockBackEvent();
private:	
	UFUNCTION()
	void AnimNotify_AttackHitCheck() const;
	UFUNCTION()
	void AnimNotify_AttackStopCheck() const;
	UFUNCTION()
	void AnimNotify_MoveSkipCheck() const;
	UFUNCTION()
	void AnimNotify_DodgeJumpSkipCheck() const;
	UFUNCTION()
	void AnimNotify_PerfectDodgeToAttack() const;
	UFUNCTION()
	void AnimNotify_UltimateAttackSetStack() const;
	UFUNCTION()
	void AnimNotify_UltimateAttackStackExplode() const;
	UFUNCTION()
	void AnimNotify_DashReuseStart()const;
	UFUNCTION()
	void AnimNotify_DashReuseStop()const;
	UFUNCTION()
	void AnimNotify_FootStep() const;
	UFUNCTION()
	void AnimNotify_RadialBlur() const;

	//sound
	UFUNCTION()
	void AnimNotify_TakeDamageSound() const;
	UFUNCTION()
	void AnimNotify_DodgeSound() const;
	UFUNCTION()
	void AnimNotify_PerfectDodgeSound() const;
	UFUNCTION()
	void AnimNotify_StanceChangeSound() const;
	UFUNCTION()
	void AnimNotify_StackBreakMove() const;
	UFUNCTION()
	void AnimNotify_StackBreakSlash() const;
	UFUNCTION()
	void AnimNotify_SpiritSkillSound() const;


	UFUNCTION()
	void AnimNotify_AttackSound() const;

	UFUNCTION()
	void AnimNotify_Strength() const;
	UFUNCTION()
	void AnimNotify_Normal() const;

	FName GetAttackMontageSectionName(const int32 Section);
};
