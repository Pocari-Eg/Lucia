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
	bSword = true;
}

UIreneAnimInstance::UIreneAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordAttack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireAttack_Montage.IreneFireAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearAttack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneThunderAttack_Montage.IreneThunderAttack_Montage"));
	if(SwordAttack_Montage.Succeeded()&&SpearAttack_Montage.Succeeded())
	{
		SwordAttackMontage = SwordAttack_Montage.Object;
		SpearAttackMontage = SpearAttack_Montage.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordSkill1_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireSkill1_Montage.IreneFireSkill1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordSkill2_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireSkill2_Montage.IreneFireSkill2_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpearSkill1_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneThunderSkill_Montage.IreneThunderSkill_Montage"));
	if(SwordSkill1_Montage.Succeeded()&&SwordSkill2_Montage.Succeeded()&&SpearSkill1_Montage.Succeeded())
	{
		SwordSkill1Montage = SwordSkill1_Montage.Object;
		SwordSkill2Montage = SwordSkill2_Montage.Object;
		SpearSkill1Montage = SpearSkill1_Montage.Object;
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
			IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}

void UIreneAnimInstance::PlayAttackMontage()
{
	// 현재 무기에 따라 기본공격 몽타주 실행하는 함수
	if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[0])
		Montage_Play(SwordAttackMontage, 1.0f);
	else if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[1])
		Montage_Play(SpearAttackMontage, 1.0f);
}
void UIreneAnimInstance::PlaySkillAttackMontage(const int AttackCount)
{
	// 스킬 몽타주를 실행하는 함수
	if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[0])
		Montage_Play(SwordSkill1Montage, 1.0f);
	else if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[1])
		Montage_Play(SpearSkill1Montage, 1.0f);
}

void UIreneAnimInstance::NextToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 현재 세션이 종료되면 시작시키는 함수
	if (NewSection > 1)
	{
		if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[0])
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), SwordAttackMontage);
		else if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[1])
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), SpearAttackMontage);
	}
}
void UIreneAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 즉시 시작시키는 함수
	if (NewSection > 1)
	{
		if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[0])
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), SwordAttackMontage);
		else if(Irene->Weapon->SkeletalMesh == Irene->WeaponMeshArray[1])
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), SpearAttackMontage);
	}
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

