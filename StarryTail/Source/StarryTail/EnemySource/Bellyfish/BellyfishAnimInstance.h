// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BellyfishAnimInstance.generated.h"
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FRushEndDelegate);

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
	void PlayAttackSignMontage();
	void PlayRunMontage();
	void PlayRushMontage();
	bool GetAttackIsPlaying() override;
private:
	UFUNCTION()
		void AnimNotify_RushEnd();
public:
	FRushEndDelegate RushEnd;
private:
	bool CheckAttackedMontagePlaying() override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackSignMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackSignMontage2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* WalkMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* WalkMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RushAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* RushMontage;

};
