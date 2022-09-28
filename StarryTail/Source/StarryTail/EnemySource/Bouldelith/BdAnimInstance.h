// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BdAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FBackstepEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAttackDirectionDelegate);

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
	void PlayAttack4Montage();

	void PlayAttackedMontage() override;
	void PlayBrokenMontage();

	void PlayAttack1ComboMontage();
	void PlayAttack2ComboMontage();

	void PlayLeftBattleWalkMontage();
	void PlayRightBattleWalkMontage();

	void UpgradeBattleRun();
	bool CheckAttackedMontagePlaying() override;
	bool GetAttackIsPlaying() override;
	bool GetBackstepIsPlaying();
	bool GetBattleRunIsPlaying();
	//Var


	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayDetectMontage() override;

	FAttackDelegate Attack1;
	FAttackDelegate Attack2;


	FAttackDirectionDelegate Right;
	FAttackDirectionDelegate Left;

	FAttackDelegate Attack4;
	FBackstepEndDelegate BackstepEnd;
	FAttackEndDelegate Attack1End;
	FAttackEndDelegate Attack2End;
	FAttackEndDelegate Attack3End;
	FAttackEndDelegate Attack4End;
private:
	UFUNCTION()
	void AnimNotify_Attack1();
	UFUNCTION()
	void AnimNotify_Attack2();
	
	UFUNCTION()
	void AnimNotify_Right();
	UFUNCTION()
	void AnimNotify_Left();

	UFUNCTION()
		void AnimNotify_Attack4();
	UFUNCTION()
		void AnimNotify_BackstepEnd();
	UFUNCTION()
		void AnimNotify_Attack1End();
	UFUNCTION()
		void AnimNotify_Attack2End();
	UFUNCTION()
		void AnimNotify_Attack3End();
	UFUNCTION()
		void AnimNotify_Attack4End();
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage4;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BrokenAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BrokenMontage;

	bool bIsStatue = true;
public:

	void SetbIsState(bool state);


	UFUNCTION(BlueprintCallable)
	bool GetbIsStatue() const;

};
