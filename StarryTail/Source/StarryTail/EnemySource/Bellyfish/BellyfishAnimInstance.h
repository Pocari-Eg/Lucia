// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BellyfishAnimInstance.generated.h"
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FRushEndDelegate);
DECLARE_MULTICAST_DELEGATE(FProjectileFireDelegate);
DECLARE_MULTICAST_DELEGATE(FRushStartDelegate);
UCLASS()
class STARRYTAIL_API UBellyfishAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayAttackMontage() override;
	void PlayDetectMontage() override;
	void PlayAttackedMontage() override;
	void PlayWalkMontage() override;
	void PlayAttackLoopMontage();
	void PlayRunMontage();
	void PlayRushMontage();
	void PlayFireMontage();
	bool GetAttackIsPlaying() override;


//Montage
public:
	void JumeToRushEnd();
private:
	UFUNCTION()
		void AnimNotify_RushEnd();
	UFUNCTION()
		void AnimNotify_RushStart();
	UFUNCTION()
		void AnimNotify_Fire();
public:
	FRushEndDelegate RushEnd;
	FRushStartDelegate RushStart;
	FProjectileFireDelegate Fire;
private:
	bool CheckAttackedMontagePlaying() override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RushAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* RushMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RushAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RushAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackLoopMontage;
};
