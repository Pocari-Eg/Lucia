// Fill out your copyright notice in the Description page of Project Settings.


#include "BellyfishAnimInstance.h"


void UBellyfishAnimInstance::PlayIdleMontage()
{

		if (Montage_IsPlaying(IdleMontage1) || Montage_IsPlaying(IdleMontage2))
			return;

		auto Random = FMath::RandRange(0, 1);

		if (Random == 0)
			Montage_Play(IdleMontage1, PlayRate);
		else
			Montage_Play(IdleMontage2, PlayRate);
}

void UBellyfishAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UBellyfishAnimInstance::PlayAttackMontage()
{
	
	Montage_Play(AttackMontage, PlayRate);
}

void UBellyfishAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}

void UBellyfishAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
		Montage_Play(AttackedMontage, 1.0f);
}

void UBellyfishAnimInstance::PlayWalkMontage()
{
	if (Montage_IsPlaying(WalkMontage1) || Montage_IsPlaying(WalkMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(WalkMontage1, PlayRate);
	else
		Montage_Play(WalkMontage2, PlayRate);
}

void UBellyfishAnimInstance::PlayAttackSignMontage()
{
	if (Montage_IsPlaying(AttackSignMontage1) || Montage_IsPlaying(AttackSignMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(AttackSignMontage1, PlayRate);
	else
		Montage_Play(AttackSignMontage2, PlayRate);
}

void UBellyfishAnimInstance::PlayRunMontage()
{
	if (Montage_IsPlaying(WalkMontage1) || Montage_IsPlaying(WalkMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(WalkMontage1, PlayRate);
	else
		Montage_Play(WalkMontage2, PlayRate);
}


bool UBellyfishAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(AttackMontage));
}



bool UBellyfishAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
