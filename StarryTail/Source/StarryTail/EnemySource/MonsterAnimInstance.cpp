// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	PlayRate = 1.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> IDLE_MONTAGE1(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Idle_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> IDLE_MONTAGE2(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Idle2_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> WALK_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Walk_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DETECT_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Detect_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BATTLEIDLE_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_BattleIdle_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BATTLEWALK_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_BattleWalk_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Attack1_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Attack2_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACKED_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Attacked_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> GROGGY_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Groggy_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SHOCK_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Shock_Montage"));

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("/Game/Animation/Monster/Morbit/Morbit_Montage/M_Mb_Die_Montage"));
	if (IDLE_MONTAGE1.Succeeded())
	{
		IdleMontage1 = IDLE_MONTAGE1.Object;
	}
	if (IDLE_MONTAGE2.Succeeded())
	{
		IdleMontage2 = IDLE_MONTAGE2.Object;
	}
	if (WALK_MONTAGE.Succeeded())
	{
		WalkMontage = WALK_MONTAGE.Object;
	}
	if (DETECT_MONTAGE.Succeeded())
	{
		DetectMontage = DETECT_MONTAGE.Object;
	}
	if (BATTLEIDLE_MONTAGE.Succeeded())
	{
		BattleIdleMontage = BATTLEIDLE_MONTAGE.Object;
	}
	if (BATTLEWALK_MONTAGE.Succeeded())
	{
		BattleWalkMontage = BATTLEWALK_MONTAGE.Object;
	}
	if (ATTACK_MONTAGE1.Succeeded())
	{
		MeleeAttackMontage1 = ATTACK_MONTAGE1.Object;
	}
	if (ATTACK_MONTAGE2.Succeeded())
	{
		MeleeAttackMontage2 = ATTACK_MONTAGE2.Object;
	}
	if (ATTACKED_MONTAGE.Succeeded())
	{
		AttackedMontage = ATTACKED_MONTAGE.Object;
	}
	if (GROGGY_MONTAGE.Succeeded())
	{
		GroggyMontage = GROGGY_MONTAGE.Object;
	}
	if (SHOCK_MONTAGE.Succeeded())
	{
		ShockMontage = SHOCK_MONTAGE.Object;
	}
	if (DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
	}
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
void UMonsterAnimInstance::PlayIdleMontage()
{
	if (Montage_IsPlaying(IdleMontage1) || Montage_IsPlaying(IdleMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(IdleMontage1, PlayRate);
	else
		Montage_Play(IdleMontage2, PlayRate);
}
void UMonsterAnimInstance::PlayWalkMontage()
{
	Montage_Play(WalkMontage, PlayRate);
}
void UMonsterAnimInstance::PlayDetectMontage()
{
	Montage_Play(DetectMontage, PlayRate);
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
	if(!Montage_IsPlaying(AttackedMontage))
		Montage_Play(AttackedMontage, PlayRate);
}
void UMonsterAnimInstance::PlayGroggyMontage()
{
	Montage_Play(GroggyMontage, PlayRate);
}
void UMonsterAnimInstance::PlayShockMontage()
{
	if (!Montage_IsPlaying(ShockMontage))
		Montage_Play(ShockMontage, PlayRate);
}
void UMonsterAnimInstance::PlayMeleeAttackMontage()
{
	if(Montage_IsPlaying(MeleeAttackMontage1) || Montage_IsPlaying(MeleeAttackMontage2))
		return;

	auto Random = FMath::RandRange(0, 1);

	if (Random == 0)
		Montage_Play(MeleeAttackMontage1, PlayRate);
	else
		Montage_Play(MeleeAttackMontage2, PlayRate);
}
void UMonsterAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage, 1.0f);
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
bool UMonsterAnimInstance::GetAttackIsPlaying()
{
	return (Montage_IsPlaying(MeleeAttackMontage1) || Montage_IsPlaying(MeleeAttackMontage2));
}
void UMonsterAnimInstance::AnimNotify_Attack()
{
	Attack.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AttackEnd.Broadcast();
}
void UMonsterAnimInstance::AnimNotify_Death()
{
	Death.Broadcast();
}