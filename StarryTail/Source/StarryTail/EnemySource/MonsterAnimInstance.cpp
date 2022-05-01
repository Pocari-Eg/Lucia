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
void UMonsterAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}
void UMonsterAnimInstance::PlayBattleIdleMontage()
{
	Montage_Play(BattleIdleMontage, PlayRate);
}
void UMonsterAnimInstance::PlayBattleWalkMontage()
{
	Montage_Play(BattleWalkMontage, PlayRate);
}
void UMonsterAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(AttackedMontage, 1.0f);
}
void UMonsterAnimInstance::PlayGroggyMontage()
{
	if(!Montage_IsPlaying(GroggyMontage))
		Montage_Play(GroggyMontage, PlayRate);
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