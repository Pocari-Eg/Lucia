// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "MorbitAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UMorbitAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayAttackMontage() override;
	void PlayDetectMontage() override;
	void PlayAttackedRightMontage();
	void PlayAttackedLeftMontage();
	void PlayAttackedCriticalRightMontage();
	void PlayAttackedCriticalLeftMontage();
	void PlayRollingMontage();

	bool GetAttackIsPlaying() override;
private:
	bool CheckAttackedMontagePlaying() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedRightMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedLeftMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedCriticalRightMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedCriticalLeftMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* RollingMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* MeleeAttackMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* MeleeAttackMontage2;

};
