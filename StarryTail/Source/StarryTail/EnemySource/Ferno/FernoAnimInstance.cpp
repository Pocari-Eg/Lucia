// Fill out your copyright notice in the Description page of Project Settings.


#include "FernoAnimInstance.h"


void UFernoAnimInstance::PlayIdleMontage()
{
	if (Montage_IsPlaying(IdleMontage1) || Montage_IsPlaying(IdleMontage2))
		return;
	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(IdleMontage1, PlayRate);
	else
		Montage_Play(IdleMontage2, PlayRate);
}

void UFernoAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}

void UFernoAnimInstance::PlayAttackMontage()
{
	//메테오 발사 이벤트
	if (Montage_IsPlaying(RangeAttackMontage1) || Montage_IsPlaying(RangeAttackMontage2))
		return;
	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(RangeAttackMontage1, PlayRate);
	else
		Montage_Play(RangeAttackMontage2, PlayRate);
}

void UFernoAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}

void UFernoAnimInstance::PlayRunMontage()
{
}

bool UFernoAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(RangeAttackMontage1) || Montage_IsPlaying(RangeAttackMontage2));
}



bool UFernoAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
