// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "ScAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FAddFeatherDelegate);
DECLARE_MULTICAST_DELEGATE(FFeatherAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FClawStartDelegate);

UCLASS()
class STARRYTAIL_API UScAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayFeatherRMontage();
	void PlayFeatherLMontage();
	void PlayFeatherMMontage();
	void PlayClawFMontage();
	void PlayRushMontage();
	void PlayStuckMontage();

	FAttackEndDelegate Attack1End;
	FAttackEndDelegate Attack2End;
	FAddFeatherDelegate AddFeather;
	FFeatherAttackDelegate Feather;
	FClawStartDelegate ClawStart;
private:
	UFUNCTION()
		void AnimNotify_Feather();
	UFUNCTION()
		void AnimNotify_AddFeatherCount();
	UFUNCTION()
		void AnimNotify_ClawStart();
	UFUNCTION()
		void AnimNotify_Attack1End();
	UFUNCTION()
		void AnimNotify_Attack2End();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FeatherMontageR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FeatherMontageL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FeatherMontageM;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ClawAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ClawFMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RushAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* RushMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StuckAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* StuckMontage;
};
