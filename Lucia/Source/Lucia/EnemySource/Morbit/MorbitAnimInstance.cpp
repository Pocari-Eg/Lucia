// Fill out your copyright notice in the Description page of Project Settings.


#include "MorbitAnimInstance.h"

#pragma region Attacked
void UMorbitAnimInstance::PlayAttackedRightMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedRightMontage, 1.0f);
}
void UMorbitAnimInstance::PlayAttackedLeftMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedLeftMontage, 1.0f);
}
void UMorbitAnimInstance::PlayAttackedCriticalRightMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedCriticalRightMontage, 1.0f);
}
void UMorbitAnimInstance::PlayAttackedCriticalLeftMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedCriticalLeftMontage, 1.0f);
}
void UMorbitAnimInstance::PlayRollingMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(RollingMontage);
}
#pragma endregion
#pragma region Attack
void UMorbitAnimInstance::PlayAttackMontage()
{
	if (Montage_IsPlaying(MeleeAttackMontage1) || Montage_IsPlaying(MeleeAttackMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(MeleeAttackMontage1, PlayRate);
	else
		Montage_Play(MeleeAttackMontage2, PlayRate);
}
#pragma endregion
void UMorbitAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}
void UMorbitAnimInstance::PlayIdleMontage()
{
	if (Montage_IsPlaying(IdleMontage1) || Montage_IsPlaying(IdleMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(IdleMontage1, PlayRate);
	else
		Montage_Play(IdleMontage2, PlayRate);
}
void UMorbitAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}
bool UMorbitAnimInstance::CheckAttackedMontagePlaying()
{
	if (Montage_IsPlaying(AttackedMontage))
		return true;
	if (Montage_IsPlaying(AttackedRightMontage))
		return true;
	if (Montage_IsPlaying(AttackedLeftMontage))
		return true;
	if (Montage_IsPlaying(GroggyMontage))
		return true;
	if (Montage_IsPlaying(RollingMontage))
		return true;

	return false;
}
bool UMorbitAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(MeleeAttackMontage1) || Montage_IsPlaying(MeleeAttackMontage2));
}