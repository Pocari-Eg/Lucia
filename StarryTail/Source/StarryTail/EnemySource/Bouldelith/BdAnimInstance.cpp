// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAnimInstance.h"

void UBdAnimInstance::PlayDetectMontage()
{
	Montage_Play(DetectMontage);
}
void UBdAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}
void UBdAnimInstance::PlayBattleRunMontage()
{
	if (Montage_IsPlaying(BattleRunMontage1))
		return;

	Montage_Play(BattleRunMontage1);
}
void UBdAnimInstance::PlayBackstepMontage()
{
	if (Montage_IsPlaying(BackstepMontage))
		return;
	Montage_Play(BackstepMontage);
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
void UBdAnimInstance::PlayBattleWalkMontage()
{
	if (Montage_IsPlaying(BattleLeftWalkMontage) || Montage_IsPlaying(BattleRightWalkMontage))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(BattleLeftWalkMontage);
	else
		Montage_Play(BattleRightWalkMontage);
}
#pragma region Attack
void UBdAnimInstance::PlayAttack1Montage()
{
	Montage_Play(AttackMontage1);
}
void UBdAnimInstance::PlayAttack2Montage()
{
	Montage_Play(AttackMontage2);
}
void UBdAnimInstance::PlayAttack3Montage()
{
	Montage_Play(AttackMontage3);
}
void UBdAnimInstance::PlayAttack1ComboMontage()
{
	Montage_Play(AttackComboMontage1);
}
void UBdAnimInstance::PlayAttack2ComboMontage()
{
	Montage_Play(AttackComboMontage2);
}
#pragma endregion
void UBdAnimInstance::UpgradeBattleRun()
{
	if (Montage_IsPlaying(BattleRunMontage3))
		return;

	if (Montage_IsPlaying(BattleRunMontage1))
		Montage_Play(BattleRunMontage2);
	else if (Montage_IsPlaying(BattleRunMontage2))
		Montage_Play(BattleRunMontage3);
}
void UBdAnimInstance::AnimNotify_BackstepEnd()
{
	BackstepEnd.Broadcast();
}
void UBdAnimInstance::AnimNotify_Attack1End()
{
	Attack1End.Broadcast();
}
void UBdAnimInstance::AnimNotify_Attack2End()
{
	Attack2End.Broadcast();
}
void UBdAnimInstance::AnimNotify_Attack3End()
{
	Attack3End.Broadcast();
}