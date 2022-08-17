// Fill out your copyright notice in the Description page of Project Settings.


#include "StrainAnimInstance.h"


void UStrainAnimInstance::PlayIdleMontage()
{

		if (Montage_IsPlaying(IdleMontage1) || Montage_IsPlaying(IdleMontage2))
			return;

		auto Random = FMath::RandRange(0, 1);

		if (Random == 0)
			Montage_Play(IdleMontage1, PlayRate);
		else
			Montage_Play(IdleMontage2, PlayRate);
}

void UStrainAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UStrainAnimInstance::PlayAttackMontage()
{
	
	Montage_Play(AttackMontage, PlayRate);
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

void UStrainAnimInstance::PlayWalkMontage()
{
	if (Montage_IsPlaying(WalkMontage1) || Montage_IsPlaying(WalkMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(WalkMontage1, PlayRate);
	else
		Montage_Play(WalkMontage2, PlayRate);
}

void UStrainAnimInstance::PlayAttackSignMontage()
{
	if (Montage_IsPlaying(AttackSignMontage1) || Montage_IsPlaying(AttackSignMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(AttackSignMontage1, PlayRate);
	else
		Montage_Play(AttackSignMontage2, PlayRate);
}

void UStrainAnimInstance::PlayRunMontage()
{
	if (Montage_IsPlaying(WalkMontage1) || Montage_IsPlaying(WalkMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(WalkMontage1, PlayRate);
	else
		Montage_Play(WalkMontage2, PlayRate);
}


bool UStrainAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(AttackMontage));
}



bool UStrainAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
