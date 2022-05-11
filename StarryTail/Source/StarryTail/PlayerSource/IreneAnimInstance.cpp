// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IreneAnimInstance.h"

#include "IreneAttackInstance.h"
#include "IreneCharacter.h"

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
	TargetMonster = FVector::ZeroVector;
}

UIreneAnimInstance::UIreneAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Fire_Attack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneBaseAttack_Montage.IreneBaseAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Fire_Skill_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneMagicAttack1_Montage.IreneMagicAttack1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Water_Attack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneBaseAttack_Montage.IreneBaseAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Water_Skill_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneMagicAttack1_Montage.IreneMagicAttack1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Thunder_Attack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneBaseAttack_Montage.IreneBaseAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Thunder_Skill_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneMagicAttack1_Montage.IreneMagicAttack1_Montage"));

	if(Fire_Attack_Montage.Succeeded())
	{
		FireAttackMontage = Fire_Attack_Montage.Object;
	}
	if (Fire_Skill_Montage.Succeeded())
	{
		FireSkillMontage = Fire_Skill_Montage.Object;
	}
	if(Water_Attack_Montage.Succeeded())
	{
		WaterAttackMontage = Water_Attack_Montage.Object;
	}
	if (Water_Skill_Montage.Succeeded())
	{
		WaterSkillMontage = Water_Skill_Montage.Object;
	}
	if(Thunder_Attack_Montage.Succeeded())
	{
		ThunderAttackMontage = Thunder_Attack_Montage.Object;
	}
	if (Thunder_Skill_Montage.Succeeded())
	{
		ThunderSkillMontage = Thunder_Skill_Montage.Object;
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
	if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		Montage_Play(FireAttackMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Montage_Play(WaterAttackMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		Montage_Play(ThunderAttackMontage, 1.0f);

}
void UIreneAnimInstance::PlayEffectAttackMontage()
{
	if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		Montage_Play(FireSkillMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Montage_Play(WaterSkillMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		Montage_Play(ThunderSkillMontage, 1.0f);
}

void UIreneAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	if (NewSection > 1)
	{
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), FireAttackMontage);
		else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), WaterAttackMontage);
		else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), ThunderAttackMontage);
	}
}
void UIreneAnimInstance::JumpToEffectAttackMontageSection(const int32 NewSection)
{
	if (NewSection > 1)
	{
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), FireSkillMontage);
		else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), WaterSkillMontage);
		else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), ThunderSkillMontage);
	}
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

