// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneAnimInstance.h"

UIreneAnimInstance::UIreneAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Developers/syhwms/Collections/AnimTest/Irene_Montage.Irene_Montage"));
	if(ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UIreneAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if(::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Pawn);
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

void UIreneAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	if(NewSection > 1)
		Montage_SetNextSection(GetAttackMontageSectionName(NewSection-1),GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UIreneAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}

void UIreneAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UIreneAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"),Section));
}
