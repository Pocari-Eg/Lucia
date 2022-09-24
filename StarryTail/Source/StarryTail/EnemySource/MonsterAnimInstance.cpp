// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	PlayRate = 1.0f;
	
}
void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}
void UMonsterAnimInstance::SetPlayRate(float Value)
{
	PlayRate = Value;
}
#pragma region Montage
void UMonsterAnimInstance::PlayWalkMontage()
{
	Montage_Play(WalkMontage, PlayRate);
}
void UMonsterAnimInstance::PlayBattleIdleMontage()
{
	if (Montage_IsPlaying(BattleIdleMontage))
		return;
	Montage_Play(BattleIdleMontage, PlayRate);
}
void UMonsterAnimInstance::PlayBattleWalkMontage()
{
	Montage_Play(BattleWalkMontage, PlayRate);
}
void UMonsterAnimInstance::PlayGroggyMontage()
{
	if(!Montage_IsPlaying(GroggyMontage))
		Montage_Play(GroggyMontage, PlayRate);
}

void UMonsterAnimInstance::PlayWalktoTraceMontage()
{
	if (WalkToTraceMontage != nullptr) {
		Montage_Play(WalkToTraceMontage, PlayRate);
	}
}
#pragma endregion
bool UMonsterAnimInstance::GetBattleIdleIsPlaying()
{
	return (Montage_IsPlaying(BattleIdleMontage));
}
bool UMonsterAnimInstance::GetBattleWalkIsPlaying()
{
	return (Montage_IsPlaying(BattleWalkMontage));
}
void UMonsterAnimInstance::AnimNotify_Attack()
{
	Attack.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AttackEnd.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_AttackedEnd()
{
	AttackedEnd.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_Death()
{
	Death.Broadcast();
}

void UMonsterAnimInstance::AnimNotify_DodgeTimeOn()
{
	DodgeTimeOn.Broadcast();
}

void UMonsterAnimInstance::AnimNotify_DodgeTimeOff()
{
	DodgeTimeOff.Broadcast();
}


