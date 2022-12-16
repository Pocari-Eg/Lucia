// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../Lucia.h"
#include "IreneSpiritAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSpiritAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class LUCIA_API UIreneSpiritAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	FOnSpiritAttackHitCheckDelegate OnSpiritAttackHitCheck;
	
private:
	UPROPERTY()
	class AIreneCharacter* Irene;
	UPROPERTY()
	class AIreneSpirit* IreneSpirit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EStateEnum IreneState;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkill1Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkill2Montage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkill3Montage;

public:
	void Init(AIreneCharacter* Value);

private:
	UIreneSpiritAnimInstance();

	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
public:
	void PlaySkillAttackMontage(const int SkillNumber);
	
	void SetIreneStateAnim(const EStateEnum Value) { IreneState = Value; }
private:	
	UFUNCTION()
	void AnimNotify_SpiritAttackHitCheck() const;
};
