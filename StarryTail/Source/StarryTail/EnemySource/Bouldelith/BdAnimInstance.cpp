// Fill out your copyright notice in the Description page of Project Settings.


#include "BdAnimInstance.h"
#include "Bouldelith.h"
void UBdAnimInstance::PlayDetectMontage()
{
	Montage_Play(DetectMontage, 1.0f);
}
void UBdAnimInstance::PlayStatueMontage()
{
	Montage_Play(IdleMontage2, 0.0f);
}
void UBdAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
}
void UBdAnimInstance::PlayBattleRunMontage()
{
	if (Montage_IsPlaying(BattleRunMontage))
		return;

	Montage_Play(BattleRunMontage, PlayRate);
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
	Montage_Play(AttackMontage4, PlayRate);
}
void UBdAnimInstance::PlayAttack1ComboMontage()
{
	Montage_Play(AttackComboMontage1, PlayRate);
}
void UBdAnimInstance::PlayAttack2ComboMontage()
{
	Montage_Play(AttackComboMontage2, PlayRate);
}
void UBdAnimInstance::PlayLeftBattleWalkMontage()
{

	if (Montage_IsPlaying(BattleLeftWalkMontage))
		return;

	Montage_Play(BattleLeftWalkMontage, PlayRate);

}
void UBdAnimInstance::PlayRightBattleWalkMontage()
{

	if (Montage_IsPlaying(BattleRightWalkMontage))
		return;

	Montage_Play(BattleRightWalkMontage, PlayRate);

}
#pragma endregion
void UBdAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedMontage, PlayRate);
}
void UBdAnimInstance::PlayBrokenMontage()
{
	Montage_Play(BrokenMontage, PlayRate);
}

void UBdAnimInstance::UpgradeBattleRun()
{

	if (Montage_IsPlaying(BattleRunMontage))
		Montage_Play(BattleRunMontage, PlayRate);

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
	if (Montage_IsPlaying(BattleRunMontage))
		return true;


	return false;
}
void UBdAnimInstance::AnimNotify_Attack1()
{
	Attack1.Broadcast();
}
void UBdAnimInstance::AnimNotify_Attack2()
{
	Attack2.Broadcast();
}

void UBdAnimInstance::AnimNotify_Right()
{
	Right.Broadcast();
}

void UBdAnimInstance::AnimNotify_Left()
{
	Left.Broadcast();
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

void UBdAnimInstance::AnimNotify_BdAttackSound()
{
	Bouldelith->GetBdSound()->PlayBDAttackSound(Bouldelith->GetTransform());
}

void UBdAnimInstance::AnimNotify_BdQuakeSound()
{
	Bouldelith->GetBdSound()->PlayBDQuakeSound(Bouldelith->GetTransform());
}

void UBdAnimInstance::AnimNotify_DeathSound()
{
	Bouldelith->GetBdSound()->PlayBDDeathSound(Bouldelith->GetTransform());
}

void UBdAnimInstance::AnimNotify_GroggySound()
{
	Bouldelith->GetBdSound()->PlayBDGroggySound(Bouldelith->GetTransform());
}

void UBdAnimInstance::AnimNotify_RushSound()
{
	Bouldelith->GetBdSound()->PlayBDRushSound(Bouldelith->GetTransform());
}



void UBdAnimInstance::SetbIsState(bool state)
{
	bIsStatue = state;
}

void UBdAnimInstance::Init(ABouldelith* Value)
{
	Bouldelith = Value;
}

bool UBdAnimInstance::GetbIsStatue() const
{
	return bIsStatue;
}
