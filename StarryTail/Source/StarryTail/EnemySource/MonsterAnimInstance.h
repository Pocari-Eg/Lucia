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
DECLARE_MULTICAST_DELEGATE(FAttackedEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDeathDelegate);
DECLARE_MULTICAST_DELEGATE(FDodgeTimeSwitch);
UCLASS()
class STARRYTAIL_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayAttackMontage() {};
	virtual void PlayIdleMontage() {};
	virtual void PlayWalkMontage();
	virtual void PlayDetectMontage() {};
	virtual void PlayBattleIdleMontage();
	virtual void PlayBattleWalkMontage();
	virtual void PlayAttackedMontage() {};
	virtual void PlayGroggyMontage();
	virtual void PlayDeathMontage() {};
	virtual void PlayWalktoTraceMontage();

	bool GetBattleIdleIsPlaying();
	virtual bool GetAttackIsPlaying() { return true;  };
	bool GetBattleWalkIsPlaying();

	void SetPlayRate(float Value);
	
	//다이나믹 설정
	
	FAttackDelegate Attack;
	FAttackEndDelegate AttackEnd;
	FAttackedEndDelegate AttackedEnd;
	FDeathDelegate Death;
	FDodgeTimeSwitch DodgeTimeOn;
	FDodgeTimeSwitch DodgeTimeOff;

protected:
	//Function
	UFUNCTION()
		void AnimNotify_Attack();
	UFUNCTION()
		void AnimNotify_AttackEnd();
	UFUNCTION()
		void AnimNotify_AttackedEnd();
	UFUNCTION()
		void AnimNotify_Death();
	UFUNCTION()
	void AnimNotify_DodgeTimeOn();
	UFUNCTION()
	void AnimNotify_DodgeTimeOff();
	//Variable
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AnimationSpeed, Meta = (AllowPrivateAccess = true))
		float PlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WalkAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* WalkMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DetectAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DetectMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleIdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleIdleMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleWalkAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleWalkMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GroggyAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* GroggyMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeathAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DeathMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DeathAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* WalkToTraceMontage;
private:
	virtual bool CheckAttackedMontagePlaying() { return true; };
	/*
	bool bIsWalk;
	bool bIsBattleWalk;
	bool bIsIdle;
	bool bIsBattleIdle;
	bool bIsDetect;
	*/
};
