// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IreneAnimInstance.h"

UIreneAnimInstance::UIreneAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsSprintState = false;
	IsSprintStop = false;
	IreneState = EStateEnum::Idle;
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Animation/Irene/BP/IreneBaseAttack_Montage.IreneBaseAttack_Montage"));
	//static ConstructorHelpers::FObjectFinder<UAnimMontage> Effect_ATTACK_MONTAGE(TEXT("/Game/Animation/Irene/BP/IreneMagicAttack1_Montage.IreneMagicAttack1_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/Game/Model/Irene/Animation/BP/IreneBaseAttack_Montage.IreneBaseAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Effect_Attack_Montage(TEXT("/Game/Model/Irene/Animation/BP/IreneMagicAttack1_Montage.IreneMagicAttack1_Montage"));

	if(Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}
	if (Effect_Attack_Montage.Succeeded())
	{
		EffectAttackMontage = Effect_Attack_Montage.Object;
	}
}

void UIreneAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	const auto Pawn = TryGetPawnOwner();
	if(::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		const auto Character = Cast<ACharacter>(Pawn);
		if(Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
		}		
	}
}

void UIreneAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);
}
void UIreneAnimInstance::PlayEffectAttackMontage()
{
	Montage_Play(EffectAttackMontage, 1.0f);
}

void UIreneAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	if (NewSection > 1)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), AttackMontage);
}
void UIreneAnimInstance::JumpToEffectAttackMontageSection(const int32 NewSection)
{
	if (NewSection > 1)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), EffectAttackMontage);
}

void UIreneAnimInstance::AnimNotify_AttackHitCheck() const
{
	OnAttackHitCheck.Broadcast();
}

void UIreneAnimInstance::AnimNotify_NextAttackCheck() const
{
	OnNextAttackCheck.Broadcast();
}

void UIreneAnimInstance::AnimNotify_AttackStopCheck() const
{
	OnAttackStopCheck.Broadcast();
}

void UIreneAnimInstance::AnimNotify_FootStep() const
{
	OnFootStep.Broadcast();
}

FName UIreneAnimInstance::GetAttackMontageSectionName(const int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}

