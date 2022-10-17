// Fill out your copyright notice in the Description page of Project Settings.


#include "BellarusAnimInstance.h"


void UBellarusAnimInstance::PlayIdleMontage()
{

		if (Montage_IsPlaying(IdleMontage))
			return;


			Montage_Play(IdleMontage, PlayRate);
}

void UBellarusAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UBellarusAnimInstance::PlayAttackMontage()
{
	
	Montage_Play(AttackMontage, PlayRate);
}

void UBellarusAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}

void UBellarusAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
		Montage_Play(AttackedMontage, 1.0f);
}

void UBellarusAnimInstance::PlayWalkMontage()
{
	if (Montage_IsPlaying(WalkMontage))
		return;

		Montage_Play(WalkMontage, PlayRate);
}


bool UBellarusAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(AttackMontage));
}



bool UBellarusAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
