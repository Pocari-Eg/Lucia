// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneSpiritAnimInstance.h"

#include "../IreneCharacter.h"

UIreneSpiritAnimInstance::UIreneSpiritAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_1_Montage(TEXT("/Game/Animation/Irene/Animation/BP/Spirit_1_Montage.Spirit_1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_2_Montage(TEXT("/Game/Animation/Irene/Animation/BP/Spirit_1_Montage.Spirit_2_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_3_Montage(TEXT("/Game/Animation/Irene/Animation/BP/Spirit_1_Montage.Spirit_3_Montage"));
	if(Spirit_1_Montage.Succeeded()&&Spirit_2_Montage.Succeeded()&&Spirit_3_Montage.Succeeded())
	{
		SpiritSkill1Montage = Spirit_1_Montage.Object;
		SpiritSkill2Montage = Spirit_2_Montage.Object;
		SpiritSkill3Montage = Spirit_3_Montage.Object;
	}
}

void UIreneSpiritAnimInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
}
void UIreneSpiritAnimInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
void UIreneSpiritAnimInstance::InitMemberVariable()
{
	IreneState = EStateEnum::Idle;
}

void UIreneSpiritAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UIreneSpiritAnimInstance::PlaySkillAttackMontage(const int SkillNumber)
{
	switch (SkillNumber)
	{
	case 1:
		Montage_Play(SpiritSkill1Montage);
		break;
	case 2:
		Montage_Play(SpiritSkill2Montage);
		break;
	case 3:
		Montage_Play(SpiritSkill3Montage);
		break;
	default:
		break;
	}
}

void UIreneSpiritAnimInstance::AnimNotify_SpiritAttackHitCheck() const
{
	OnSpiritAttackHitCheck.Broadcast();
}

