// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IreneAnimInstance.h"

#include "IreneAttackInstance.h"
#include "IreneInputInstance.h"
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
	IsStartBreakAttack = false;
	IsMoveStopBreakAttack = false;
	IsDoAttackBreakAttack = false;
	IreneState = EStateEnum::Idle;
	IsHaveTargetMonster = false;
	TargetMonster = nullptr;
}

UIreneAnimInstance::UIreneAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordAttack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireAttack_Montage.IreneFireAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpiritAttack_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneSpiritAttack_Montage.IreneSpiritAttack_Montage"));
	if(SwordAttack_Montage.Succeeded() && SpiritAttack_Montage.Succeeded())
	{
		SwordAttackMontage = SwordAttack_Montage.Object;
		SpiritAttackMontage = SpiritAttack_Montage.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordSkill1_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireSkill1_Montage.IreneFireSkill1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SwordSkill2_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneFireSkill2_Montage.IreneFireSkill2_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_1_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneSpiritSkill_1_Montage.IreneSpiritSkill_1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_2_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneSpiritSkill_2_Montage.IreneSpiritSkill_2_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Spirit_3_Montage(TEXT("/Game/Animation/Irene/Animation/BP/IreneSpiritSkill_3_Montage.IreneSpiritSkill_3_Montage"));
	
	if(SwordSkill1_Montage.Succeeded()&&SwordSkill2_Montage.Succeeded()&&Spirit_1_Montage.Succeeded()&&Spirit_2_Montage.Succeeded()&&Spirit_3_Montage.Succeeded())
	{
		SwordSkill1Montage = SwordSkill1_Montage.Object;
		SwordSkill2Montage = SwordSkill2_Montage.Object;
		SpiritSkill1Montage = Spirit_1_Montage.Object;
		SpiritSkill2Montage = Spirit_2_Montage.Object;
		SpiritSkill3Montage = Spirit_3_Montage.Object;
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
	if(!Irene->bIsSpiritStance)
		Montage_Play(SwordAttackMontage, 1.0f);
	else
		Montage_Play(SpiritAttackMontage, 1.0f);
}
void UIreneAnimInstance::PlaySkillAttackMontage(const int AttackCount)
{
	// 스킬 몽타주를 실행하는 함수
	if(!Irene->bIsSpiritStance)
	{
		if(Irene->IreneState->GetStateToString().Compare("Sword_Skill_1") == 0)
			Montage_Play(SwordSkill1Montage, 1.0f);
		else if(Irene->IreneState->GetStateToString().Compare("Sword_Skill_2") == 0)
			Montage_Play(SwordSkill2Montage, 1.0f);
	}
	else
	{
		switch (Irene->IreneInput->GetSpiritChainAttackCount())
		{
		case 1:
			Montage_Play(SpiritSkill1Montage, 1.0f);
			break;
		case 2:
			Montage_Play(SpiritSkill2Montage, 1.0f);
			break;
		case 3:
			Montage_Play(SpiritSkill3Montage, 1.0f);
			break;
		default:
			break;
		}
	}
}

void UIreneAnimInstance::NextToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 현재 세션이 종료되면 시작시키는 함수
	if (NewSection > 1)
	{
		if(!Irene->bIsSpiritStance)
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), SwordAttackMontage);
		else
			Montage_SetNextSection(GetAttackMontageSectionName(NewSection - 1), GetAttackMontageSectionName(NewSection), SpiritAttackMontage);
	}
}
void UIreneAnimInstance::JumpToAttackMontageSection(const int32 NewSection)
{
	// 다음 기본공격의 세션을 즉시 시작시키는 함수
	if (NewSection > 1)
	{
		if(!Irene->bIsSpiritStance)
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), SwordAttackMontage);
		else
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), SpiritAttackMontage);
	}	
}

void UIreneAnimInstance::CallCreateTail()
{
	if (Irene != nullptr)
	{
	  Irene->CreateTailEvent();
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

void UIreneAnimInstance::AnimNotify_PerfectDodgeToAttack() const
{
	Irene->IreneInput->PerfectDodgePlayOver();
}

void UIreneAnimInstance::AnimNotify_UltimateAttackSetStack() const
{
	Irene->IreneInput->UltimateAttackSetStack();
}

void UIreneAnimInstance::AnimNotify_UltimateAttackStackExplode() const
{
	Irene->IreneInput->UltimateAttackStackExplode();
}

void UIreneAnimInstance::AnimNotify_DashReuseStart() const
{
	//Irene->IreneInput->SetIsDodgeToDodge(true);
}
void UIreneAnimInstance::AnimNotify_DashReuseStop() const
{
	//Irene->IreneInput->SetIsDodgeToDodge(false);
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

void UIreneAnimInstance::AnimNotify_DodgeSound() const
{
		Irene->IreneSound->PlayDodgeSound(0.0f);
}
void UIreneAnimInstance::AnimNotify_PerfectDodgeSound() const
{
  Irene->IreneSound->PlayDodgeSound(1.0f);
}
void UIreneAnimInstance::AnimNotify_StanceChangeSound() const
{

	if (Irene->bIsSpiritStance)
		Irene->IreneSound->PlayStanceChangeSound(0.0f);
}

void UIreneAnimInstance::AnimNotify_SkillSound() const
{
	Irene->IreneSound->PlaySkillVoiceSound();
}

void UIreneAnimInstance::AnimNotify_StackBreakMove() const
{

	Irene->IreneSound->PlayStackBreakMove(Irene->GetTransform());
}

void UIreneAnimInstance::AnimNotify_StackBreakSlash() const
{
	STARRYLOG_S(Error);
	Irene->IreneSound->PlayStackBreakSlash(Irene->GetTransform());
}

void UIreneAnimInstance::AnimNotify_SkillVoice1() const
{
	Irene->IreneSound->PlaySkillVoice1Sound();
}

void UIreneAnimInstance::AnimNotify_AttackSound() const
{

	if(Irene->bIsSpiritStance)
	Irene->IreneSound->PlayAttackSound(0.0f);
	else {
		Irene->IreneSound->PlayAttackSound(1.0f);
	}
}

FName UIreneAnimInstance::GetAttackMontageSectionName(const int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}

