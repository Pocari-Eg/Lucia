// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAIController.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDeathDelegate);
UCLASS()
class STARRYTAIL_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayMeleeAttackMontage();
	virtual void PlayIdleMontage();
	void PlayWalkMontage();
	void PlayDetectMontage();
	void PlayBattleIdleMontage();
	void PlayBattleWalkMontage();
	void PlayAttackedMontage();
	void PlayGroggyMontage();
	void PlayShockMontage();
	void PlayDeathMontage();

	bool GetBattleIdleIsPlaying();
	bool GetAttackIsPlaying();
	bool GetShockIsPlaying();
	bool GetBattleWalkIsPlaying();

	void SetPlayRate(float Value);
	
	//다이나믹 설정
	
	FAttackDelegate Attack;
	FAttackEndDelegate AttackEnd;
	FDeathDelegate Death;
protected:
	//Function
	UFUNCTION()
		void AnimNotify_Attack();
	UFUNCTION()
		void AnimNotify_AttackEnd();
	UFUNCTION()
		void AnimNotify_Death();

	//Variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationSpeed, Meta = (AllowPrivateAccess = true))
		float PlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WalkAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* WalkMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DetectAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DetectMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleIdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleIdleMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleWalkAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleWalkMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* MeleeAttackMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* MeleeAttackMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GroggyAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* GroggyMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ShockAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ShockMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeathAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DeathMontage;

	/*
	bool bIsWalk;
	bool bIsBattleWalk;
	bool bIsIdle;
	bool bIsBattleIdle;
	bool bIsDetect;
	*/
};
