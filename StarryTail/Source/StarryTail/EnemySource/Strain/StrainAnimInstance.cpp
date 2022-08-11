// Fill out your copyright notice in the Description page of Project Settings.


#include "StrainAnimInstance.h"


void UStrainAnimInstance::PlayIdleMontage()
{
	
		Montage_Play(IdleMontage, PlayRate);

}

void UStrainAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UStrainAnimInstance::PlayAttackMontage()
{
	
	Montage_Play(RangeAttackMontage, PlayRate);

}

void UStrainAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}

void UStrainAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
		Montage_Play(AttackedMontage, 1.0f);
}

void UStrainAnimInstance::PlayRunMontage()
{
	Montage_Play(RunMontage, PlayRate);
}


bool UStrainAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(RangeAttackMontage));
}



bool UStrainAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
