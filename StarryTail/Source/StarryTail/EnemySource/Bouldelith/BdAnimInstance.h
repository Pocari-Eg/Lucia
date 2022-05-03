// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BdAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBdAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayBattleRunMontage();
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* IdleMontage2;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BattleRunAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* BattleRunMontage1;
public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
};
