// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BellarusAnimInstance.generated.h"
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FAttackEndDelegate);

UCLASS()
class STARRYTAIL_API UBellarusAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
	
public:
	FAttackDelegate WingLAttack;
	FAttackDelegate WingRAttack;
	FAttackDelegate TailAttack;

	FAttackEndDelegate WingLEnd;
	FAttackEndDelegate WingREnd;
	FAttackEndDelegate TailEnd;


public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayDetectMontage() override;
	void PlayAttackedMontage() override;
	void PlayWalkMontage() override;


	void PlayWingLMontage();
	void PlayWingRMontage();
	void PlayTailMontage();


	UFUNCTION()
	void AnimNotify_Tail();
	UFUNCTION()
	void AnimNotify_WingL();
	UFUNCTION()
	void AnimNotify_WingR();
private:
	bool CheckAttackedMontagePlaying() override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* IdleMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WingLMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WingRMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* TailMontage;

};
