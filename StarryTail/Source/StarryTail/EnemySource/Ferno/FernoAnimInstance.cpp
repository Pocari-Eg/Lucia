// Fill out your copyright notice in the Description page of Project Settings.


#include "FernoAnimInstance.h"


void UFernoAnimInstance::PlayIdleMontage()
{
	
		Montage_Play(IdleMontage, PlayRate);

}

void UFernoAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UFernoAnimInstance::PlayAttackMontage()
{
	
		Montage_Play(RangeAttackMontage, PlayRate);

}

void UFernoAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}

void UFernoAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
		Montage_Play(AttackedMontage, 1.0f);
}

void UFernoAnimInstance::PlayRunMontage()
{
	Montage_Play(RunMontage, PlayRate);
}


bool UFernoAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(RangeAttackMontage));
}



bool UFernoAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
