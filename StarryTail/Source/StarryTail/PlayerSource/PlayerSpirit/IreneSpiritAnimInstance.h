// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../StarryTail.h"
#include "IreneSpiritAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSpiritAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UIreneSpiritAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	FOnSpiritAttackHitCheckDelegate OnSpiritAttackHitCheck;
	
private:
	UPROPERTY()
	class AIreneCharacter* Irene;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EStateEnum IreneState;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* SpiritSkillMontage;

public:
	void Init(AIreneCharacter* Value);

private:
	UIreneSpiritAnimInstance();

	virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
public:
	void PlaySkillAttackMontage();
	void NextToAttackMontageSection(const int32 NewSection);
	void JumpToAttackMontageSection(const int32 NewSection);
	
	void SetIreneStateAnim(const EStateEnum Value) { IreneState = Value; }

private:	
	UFUNCTION()
	void AnimNotify_SpiritAttackHitCheck() const;

	FName GetAttackMontageSectionName(const int32 Section);
};
