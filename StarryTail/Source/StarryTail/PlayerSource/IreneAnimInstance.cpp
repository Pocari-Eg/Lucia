// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IreneAnimInstance.h"

#include "IreneAttackInstance.h"
#include "IreneFSM.h"
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
	TargetMonster = nullptr;
}

UIreneAnimInstance::UIreneAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Fire_Attack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireAttack_Montage.IreneFireAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Fire_Skill1_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireSkill1_Montage.IreneFireSkill1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Fire_Skill2_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireSkill2_Montage.IreneFireSkill2_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Water_Attack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneWaterAttack_Montage.IreneWaterAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Water_Skill_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneWaterSkill_Montage.IreneWaterSkill_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Thunder_Attack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneThunderAttack_Montage.IreneThunderAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Thunder_Skill_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneThunderSkill_Montage.IreneThunderSkill_Montage"));

	if(Fire_Attack_Montage.Succeeded())
	{
		FireAttackMontage = Fire_Attack_Montage.Object;
	}
	if (Fire_Skill1_Montage.Succeeded())
	{
	 	FireSkill1Montage = Fire_Skill1_Montage.Object;
	}
	if (Fire_Skill2_Montage.Succeeded())
	{
		FireSkill2Montage = Fire_Skill2_Montage.Object;
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
	// 현재 속성에 따라 기본공격 몽타주 실행하는 함수
	if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
		Montage_Play(FireAttackMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Montage_Play(WaterAttackMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		Montage_Play(ThunderAttackMontage, 1.0f);

}
void UIreneAnimInstance::PlaySkillAttackMontage(const int AttackCount)
{
	// 현재 속성에 따라 스킬 몽타주를 실행하는 함수
	if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
	{
		if(AttackCount == 2)
			Montage_Play(FireSkill2Montage, 1.0f);
		else
			Montage_Play(FireSkill1Montage, 1.0f);
	}
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
		Montage_Play(WaterSkillMontage, 1.0f);
	else if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
		Montage_Play(ThunderSkillMontage, 1.0f);
}

void UIreneAnimInstance::NextToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 현재 세션이 종료되면 시작시키는 함수
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
void UIreneAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 즉시 시작시키는 함수
	if (NewSection > 1)
	{
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Fire)
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), FireAttackMontage);
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Water)
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), WaterAttackMontage);
		if(Irene->IreneAttack->GetAttribute() == EAttributeKeyword::e_Thunder)
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), ThunderAttackMontage);
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

void UIreneAnimInstance::AnimNotify_MoveSkipCheck() const
{
	Irene->IreneAttack->SetCanMoveSkip(true);
}

void UIreneAnimInstance::AnimNotify_DodgeJumpSkipCheck() const
{
	Irene->IreneAttack->SetCanDodgeJumpSkip(true);
}

void UIreneAnimInstance::AnimNotify_ReAttackCheck() const
{
	Irene->IreneAttack->SetCanReAttackSkip(true);
}

void UIreneAnimInstance::AnimNotify_SkillSkipCheck() const
{
	Irene->IreneAttack->SetCanSkillSkip(true);
}

void UIreneAnimInstance::AnimNotify_FootStep() const
{
	OnFootStep.Broadcast();
}

void UIreneAnimInstance::AnimNotify_RadialBlur() const
{
	OnRadialBlur.Broadcast();
}

FName UIreneAnimInstance::GetAttackMontageSectionName(const int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}

