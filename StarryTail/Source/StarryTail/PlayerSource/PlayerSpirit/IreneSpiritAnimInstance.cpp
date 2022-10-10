// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneSpiritAnimInstance.h"

#include "../IreneCharacter.h"

UIreneSpiritAnimInstance::UIreneSpiritAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_Montage(TEXT("/Game/Animation/Irene/Animation/BP/Spirit_Montage.Spirit_Montage"));
	if(Spirit_Montage.Succeeded())
	{
		SpiritSkillMontage = Spirit_Montage.Object;
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

void UIreneSpiritAnimInstance::PlaySkillAttackMontage()
{
	// ��ų ��Ÿ�ָ� �����ϴ� �Լ�
	Montage_Play(SpiritSkillMontage, 1.0f);
}

void UIreneSpiritAnimInstance::NextToAttackMontageSection(const int32 NewSection)
{
	// ���� �⺻������ ������ ���� ������ ����Ǹ� ���۽�Ű�� �Լ�
	if (NewSection > 1)
	{
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), SpiritSkillMontage);
	}
}
void UIreneSpiritAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	// ���� �⺻������ ������ ��� ���۽�Ű�� �Լ�
	if (NewSection > 1)
	{
		Montage_JumpToSection(GetAttackMontageSectionName(NewSection), SpiritSkillMontage);
	}
}

void UIreneSpiritAnimInstance::AnimNotify_SpiritAttackHitCheck() const
{
	OnSpiritAttackHitCheck.Broadcast();
}

FName UIreneSpiritAnimInstance::GetAttackMontageSectionName(const int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}

