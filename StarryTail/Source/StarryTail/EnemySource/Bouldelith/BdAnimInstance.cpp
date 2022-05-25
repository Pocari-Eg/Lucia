// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAnimInstance.h"

void UBdAnimInstance::PlayDetectMontage()
{
	Montage_Play(DetectMontage, 1.0f);
}
void UBdAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
}
void UBdAnimInstance::PlayBattleRunMontage()
{
	if (Montage_IsPlaying(BattleRunMontage1))
		return;

	Montage_Play(BattleRunMontage1, PlayRate);
}
void UBdAnimInstance::PlayBackstepMontage()
{
	if (Montage_IsPlaying(BackstepMontage))
		return;
	Montage_Play(BackstepMontage, 1.0f);
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
		Montage_Play(BattleLeftWalkMontage, PlayRate);
	else
		Montage_Play(BattleRightWalkMontage, PlayRate);
}
#pragma region Attack
void UBdAnimInstance::PlayAttack1Montage()
{
	Montage_Play(AttackMontage1, PlayRate);
}
void UBdAnimInstance::PlayAttack2Montage()
{
	Montage_Play(AttackMontage2, PlayRate);
}
void UBdAnimInstance::PlayAttack3Montage()
{
	Montage_Play(AttackMontage3, PlayRate);
}
void UBdAnimInstance::PlayAttack4Montage()
{
	Montage_Play(AttackMontage4, 1.0f);
}
void UBdAnimInstance::PlayAttack1ComboMontage()
{
	Montage_Play(AttackComboMontage1, PlayRate);
}
void UBdAnimInstance::PlayAttack2ComboMontage()
{
	Montage_Play(AttackComboMontage2, PlayRate);
}
#pragma endregion
void UBdAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedMontage, 1.0f);
}
void UBdAnimInstance::PlayBrokenMontage()
{
	Montage_Play(BrokenMontage, 1.0f);
}

void UBdAnimInstance::UpgradeBattleRun()
{
	if (Montage_IsPlaying(BattleRunMontage3))
		return;

	if (Montage_IsPlaying(BattleRunMontage1))
		Montage_Play(BattleRunMontage2, PlayRate);
	else if (Montage_IsPlaying(BattleRunMontage2))
		Montage_Play(BattleRunMontage3, PlayRate);
}
bool UBdAnimInstance::CheckAttackedMontagePlaying()
{
	if (Montage_IsPlaying(AttackedMontage))
		return true;
	if (Montage_IsPlaying(GroggyMontage))
		return true;
	if (Montage_IsPlaying(BrokenMontage))
		return true;

	return false;
}
bool UBdAnimInstance::GetAttackIsPlaying()
{
	if (Montage_IsPlaying(AttackMontage1))
		return true;
	if (Montage_IsPlaying(AttackMontage2))
		return true;
	if (Montage_IsPlaying(AttackMontage3))
		return true;
	if (Montage_IsPlaying(AttackMontage4))
		return true;

	return false;

}
bool UBdAnimInstance::GetBackstepIsPlaying()
{
	if (Montage_IsPlaying(BackstepMontage))
		return true;

	return false;
}
bool UBdAnimInstance::GetBattleRunIsPlaying()
{
	if (Montage_IsPlaying(BattleRunMontage1))
		return true;
	if (Montage_IsPlaying(BattleRunMontage2))
		return true;
	if (Montage_IsPlaying(BattleRunMontage3))
		return true;

	return false;
}
void UBdAnimInstance::AnimNotify_Attack4()
{
	Attack4.Broadcast();
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
void UBdAnimInstance::AnimNotify_Attack4End()
{
	Attack4End.Broadcast();
}