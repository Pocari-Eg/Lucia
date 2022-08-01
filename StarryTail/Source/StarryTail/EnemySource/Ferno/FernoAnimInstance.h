// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "FernoAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UFernoAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayAttackMontage() override;
	void PlayDetectMontage() override;
	void PlayAttackedMontage() override;
	void PlayRunMontage();


	bool GetAttackIsPlaying() override;
private:
	bool CheckAttackedMontagePlaying() override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* RangeAttackMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* RangeAttackMontage2;
};
