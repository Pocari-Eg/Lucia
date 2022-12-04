// Fill out your copyright notice in the Description page of Project Settings.


#include "BellyfishAnimInstance.h"
#include "Bellyfish.h"

void UBellyfishAnimInstance::PlayIdleMontage()
{

		if (Montage_IsPlaying(IdleMontage))
			return;


			Montage_Play(IdleMontage, PlayRate);
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
	if (Montage_IsPlaying(WalkMontage))
		return;

		Montage_Play(WalkMontage, PlayRate);
}



void UBellyfishAnimInstance::PlayAttackLoopMontage()
{
	Montage_Stop(0.0f);
	Montage_Play(AttackLoopMontage, PlayRate);
}

void UBellyfishAnimInstance::PlayRunMontage()
{
	if (Montage_IsPlaying(WalkMontage))
		return;

	
		Montage_Play(WalkMontage, PlayRate);
}

void UBellyfishAnimInstance::PlayRushMontage()
{
	if(RushMontage!=nullptr)
	Montage_Play(RushMontage);
}

void UBellyfishAnimInstance::PlayFireMontage()
{
	if (FireMontage != nullptr)
		Montage_Play(FireMontage);
}


bool UBellyfishAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(AttackMontage));
}

void UBellyfishAnimInstance::PlayStatueMontage()
{
	Montage_Play(IdleMontage,0.0f);
}

void UBellyfishAnimInstance::JumeToRushEnd()
{
		Montage_JumpToSection("End");
}

void UBellyfishAnimInstance::AnimNotify_RushEnd()
{

	RushEnd.Broadcast();
}

void UBellyfishAnimInstance::AnimNotify_RushStart()
{
	RushStart.Broadcast();
}

void UBellyfishAnimInstance::AnimNotify_Fire()
{
      Fire.Broadcast();
}

void UBellyfishAnimInstance::AnimNotify_BfProjectileSound()
{
	Bellyfish->GetBfSound()->PlayBfProjectile(Bellyfish->GetTransform());
}

void UBellyfishAnimInstance::AnimNotify_BfRushSound()
{
	Bellyfish->GetBfSound()->PlayBfRushAttack(Bellyfish->GetTransform());
}

void UBellyfishAnimInstance::AnimNotify_DeathSound()
{
	Bellyfish->GetBfSound()->PlayDeathSound(Bellyfish->GetTransform());
}

void UBellyfishAnimInstance::AnimNotify_GroggySound()
{
	Bellyfish->GetBfSound()->PlayGroggySound(Bellyfish->GetTransform());
}

void UBellyfishAnimInstance::AnimNotify_RangeAttackSound()
{
	Bellyfish->GetBfSound()->PlayRangeAttackSound(Bellyfish->GetTransform());
}



void UBellyfishAnimInstance::Init(ABellyfish* Value)
{
	Bellyfish = Value;
}

bool UBellyfishAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
