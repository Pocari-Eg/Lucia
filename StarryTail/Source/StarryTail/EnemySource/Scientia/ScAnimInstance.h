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
DECLARE_MULTICAST_DELEGATE(FRushStartDelegate);
DECLARE_MULTICAST_DELEGATE(FTurnEndDelegate);
DECLARE_MULTICAST_DELEGATE(FChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FChangeEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDodgeEndDelegate);
DECLARE_MULTICAST_DELEGATE(FCrushedEndDelegate);
DECLARE_MULTICAST_DELEGATE(FDropEndDelegate);

UCLASS()
class STARRYTAIL_API UScAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayFeatherRMontage();
	void PlayFeatherLMontage();
	void PlayFeatherMMontage();
	void PlayClawFMontage();
	void PlayTurnMontage();
	void PlayRushMontage();
	void PlayStuckMontage();
	void PlayChangeMontage();
	void PlayDodgeMontage();
	void PlayAttackedBAnimation();
	void PlayAttackedFAnimation();
	void PlayCrushedMontage();
	void PlayDropMontage();

	FAttackEndDelegate Attack1End;
	FAttackEndDelegate Attack2End;
	FAddFeatherDelegate AddFeather;
	FFeatherAttackDelegate Feather;
	FClawStartDelegate ClawStart;
	FRushStartDelegate RushStart;
	FTurnEndDelegate TurnEnd;
	FChangeDelegate Change;
	FChangeEndDelegate ChangeEnd;
	FDodgeEndDelegate DodgeEnd;
	FCrushedEndDelegate CrushedEnd;
	FDropEndDelegate DropEnd;
private:
	UFUNCTION()
		void AnimNotify_Feather();
	UFUNCTION()
		void AnimNotify_AddFeatherCount();
	UFUNCTION()
		void AnimNotify_ClawStart();
	UFUNCTION()
		void AnimNotify_RushStart();
	UFUNCTION()
		void AnimNotify_Attack1End();
	UFUNCTION()
		void AnimNotify_Attack2End();
	UFUNCTION()
		void AnimNotify_TurnEnd();
	UFUNCTION()
		void AnimNotify_Change();
	UFUNCTION()
		void AnimNotify_ChangeEnd();
	UFUNCTION()
		void AnimNotify_DodgeEnd();
	UFUNCTION()
		void AnimNotify_CrushedEnd();
	UFUNCTION()
		void AnimNotify_DropEnd();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurnAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* TurnMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ChangeAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* ChangeMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DodgeAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DodgeMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedFMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackedBMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CrushedAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* CrushedMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DropAnimation, Meta = (AllowPrivateAccess = true))
		UAnimMontage* DropMontage;
};
