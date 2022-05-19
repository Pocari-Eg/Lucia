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

UCLASS()
class STARRYTAIL_API UScAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayFeatherRMontage();
	void PlayFeatherLMontage();
	void PlayFeatherMMontage();

	FAttackEndDelegate Attack1End;
	FAddFeatherDelegate AddFeather;
	FFeatherAttackDelegate Feather;
private:
	UFUNCTION()
		void AnimNotify_Feather();
	UFUNCTION()
		void AnimNotify_AddFeatherCount();
	UFUNCTION()
		void AnimNotify_Attack1End();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FeatherMontageR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FeatherMontageL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* FeatherMontageM;
};
