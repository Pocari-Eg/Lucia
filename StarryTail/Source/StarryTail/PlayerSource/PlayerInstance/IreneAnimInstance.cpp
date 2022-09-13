// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IreneAnimInstance.h"

#include "IreneAttackInstance.h"
#include "IreneSoundInstance.h"
#include "../PlayerFSM/IreneFSM.h"
#include "../IreneCharacter.h"

void UIreneAnimInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
}
void UIreneAnimInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
void UIreneAnimInstance::InitMemberVariable()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;
	IsSprintState = false;
	IsSprintStop = false;
	IreneState = EStateEnum::Idle;
	IsHaveTargetMonster = false;
	TargetMonster = nullptr;
	FireChargeCount = 0;
}

UIreneAnimInstance::UIreneAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/Game/Animation/Irene/Test/NewFolder/BP/TestIreneAttack_Montage.TestIreneAttack_Montage"));
	if(Attack_Montage.Succeeded())
		AttackMontage = Attack_Montage.Object;
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill_Montage(TEXT("/Game/Animation/Irene/Test/NewFolder/BP/TestIreneSkill_Montage.TestIreneSkill_Montage"));
	if(Skill_Montage.Succeeded())
		SkillMontage = Skill_Montage.Object;
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
			IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}

void UIreneAnimInstance::PlayAttackMontage()
{
	// 현재 속성에 따라 기본공격 몽타주 실행하는 함수
	Montage_Play(AttackMontage, 1.0f);
}
void UIreneAnimInstance::PlaySkillAttackMontage(const int AttackCount)
{
	// 스킬 몽타주를 실행하는 함수
	Montage_Play(SkillMontage, 1.0f);
}

void UIreneAnimInstance::NextToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 현재 세션이 종료되면 시작시키는 함수
	if (NewSection > 1)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), AttackMontage);
}
void UIreneAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 즉시 시작시키는 함수
	if (NewSection > 1)
		Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UIreneAnimInstance::AnimNotify_AttackHitCheck() const
{
	OnAttackHitCheck.Broadcast();
}

void UIreneAnimInstance::AnimNotify_AttackStopCheck() const
{
	OnAttackStopCheck.Broadcast();
}

void UIreneAnimInstance::AnimNotify_MoveSkipCheck() const
{
	Irene->IreneAttack->SetCanMoveSkip(true);
}

void UIreneAnimInstance::AnimNotify_DodgeJumpSkipCheck() const
{
	Irene->IreneAttack->SetCanDodgeJumpSkip(true);
}

void UIreneAnimInstance::AnimNotify_FootStep() const
{
	OnFootStep.Broadcast();
}

void UIreneAnimInstance::AnimNotify_RadialBlur() const
{
	OnRadialBlur.Broadcast();
}

void UIreneAnimInstance::AnimNotify_TakeDamageSound() const
{
	Irene->IreneSound->PlayTakeDamageVoiceSound();
}
FName UIreneAnimInstance::GetAttackMontageSectionName(const int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}

