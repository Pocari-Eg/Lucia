// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAnimInstance.h"

void UBdAnimInstance::PlayBattleRunMontage()
{
	if (Montage_IsPlaying(BattleRunMontage1))
		return;

	Montage_Play(BattleRunMontage1);
}
void UBdAnimInstance::PlayIdleMontage()
{
	if (Montage_IsPlaying(IdleMontage1) || Montage_IsPlaying(IdleMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(IdleMontage1, PlayRate);
	else
		Montage_Play(IdleMontage2, PlayRate);
}
void UBdAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}