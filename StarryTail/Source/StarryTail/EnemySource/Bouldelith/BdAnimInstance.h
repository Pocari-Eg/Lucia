// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BdAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FBackstepEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttack1EndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttack2EndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttack3EndDelegate);


UCLASS()
class STARRYTAIL_API UBdAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayBattleRunMontage();
	void PlayBackstepMontage();

	void PlayAttack1Montage();
	void PlayAttack2Montage();
	void PlayAttack3Montage();

	void PlayAttackedMontage() override;

	void PlayAttack1ComboMontage();
	void PlayAttack2ComboMontage();

	void PlayBattleWalkMontage() override;

	void UpgradeBattleRun();
	bool CheckAttackedMontagePlaying() override;
	bool GetAttackIsPlaying() override;
	//Var
	FBackstepEndDelegate BackstepEnd;
	FAttack1EndDelegate Attack1End;
	FAttack2EndDelegate Attack2End;
	FAttack3EndDelegate Attack3End;
private:
	UFUNCTION()
		void AnimNotify_BackstepEnd();
	UFUNCTION()
		void AnimNotify_Attack1End();
	UFUNCTION()
		void AnimNotify_Attack2End();
	UFUNCTION()
		void AnimNotify_Attack3End();
	//Var
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackComboAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackComboMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackComboAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackComboMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleRunAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleRunMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleRunAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleRunMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleRunAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleRunMontage3;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleWalkAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleLeftWalkMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleWalkAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleRightWalkMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BackstepAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BackstepMontage;


public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayDetectMontage() override;
};
