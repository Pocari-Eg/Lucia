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
class LUCIA_API UBellarusAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
	
public:
	FAttackDelegate WingLAttack;
	FAttackDelegate WingRAttack;
	FAttackDelegate TailAttack;
	FAttackDelegate SwirlAttack;
	FAttackDelegate FeatherAttack;
	FAttackDelegate TelePortAttack;

	FAttackDelegate TelePortStart;

	FAttackEndDelegate WingLEnd;
	FAttackEndDelegate WingREnd;
	FAttackEndDelegate TailEnd;
	FAttackEndDelegate SwirlEnd;
	FAttackEndDelegate FeatherEnd;

	FAttackEndDelegate TelePortEnd;
public:
	void PlayIdleMontage() override;
	void PlayDeathMontage() override;
	void PlayDetectMontage() override;
	void PlayAttackedMontage() override;
	void PlayWalkMontage() override;


	void PlayWingLMontage();
	void PlayWingRMontage();
	void PlayTailMontage();
	void PlaySwirlMontage();
	void PlayFeatherMontage();

	void PlayStartTelePortMontage();
	void PlayEndTelePortMontage();

	UFUNCTION()
	void AnimNotify_Tail();
	UFUNCTION()
	void AnimNotify_WingL();
	UFUNCTION()
	void AnimNotify_WingR();
	UFUNCTION()
	void AnimNotify_Swirl();
	UFUNCTION()
	void AnimNotify_Feather();
	UFUNCTION()
	void AnimNotify_TelePort();
	UFUNCTION()
	void AnimNotify_TelePortAttack();
	UFUNCTION()
	void AnimNotify_DeathSound();
	UFUNCTION()
	void AnimNotify_GroggySound();
	UFUNCTION()
	void AnimNotify_WingSound();
	UFUNCTION()
	void AnimNotify_TailSound();
	UFUNCTION()
	void AnimNotify_ShootSound();
	UFUNCTION()
	void AnimNotify_TPStartSound();
	UFUNCTION()
	void AnimNotify_TPEndSound();

	void Init(class ABellarus* Value);
private:
	bool CheckAttackedMontagePlaying() override;

	class ABellarus* Bellarus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = IdleAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* IdleMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WingLMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* WingRMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* TailMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SwirlMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FeatherMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* TelePortStartMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackAnimation, Meta = (AllowPrivateAccess = true))
	UAnimMontage* TelePortEndMontage;

};
