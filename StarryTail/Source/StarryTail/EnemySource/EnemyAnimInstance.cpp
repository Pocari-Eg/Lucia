// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"


UEnemyAnimInstance::UEnemyAnimInstance()
{
	CurrentPawnSpeed = 0.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RANGED_ATTACK_MONTAGE(TEXT("/Game/Animation/Dummy_Walk_Skeleton_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MELEE_ATTACK_MONTAGE(TEXT("/Game/Animation/MeleeAttack_Montage"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RUSH_ATTACK_MONTAGE(TEXT("/Game/Animation/RushAttack_Montage"));
	if (RANGED_ATTACK_MONTAGE.Succeeded())
	{
		RangedAttackMontage = RANGED_ATTACK_MONTAGE.Object;
	}
	if (MELEE_ATTACK_MONTAGE.Succeeded())
	{
		MeleeAttackMontage = MELEE_ATTACK_MONTAGE.Object;
	}
	if (RUSH_ATTACK_MONTAGE.Succeeded())
	{
		RushAttackMontage = RUSH_ATTACK_MONTAGE.Object;
	}
}
void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();

		bCanRangedAttack = AEnemyController::bCanRangedAttack;
		bCanMeleeAttack = AEnemyController::bCanMeleeAttack;
		RangedAttackCount = AEnemyController::RangedAttackCount;
	}
}
void UEnemyAnimInstance::PlayRangedAttackMontage()
{
	Montage_Play(RangedAttackMontage, 1.0f);
}
void UEnemyAnimInstance::PlayMeleeAttackMontage()
{
	Montage_Play(MeleeAttackMontage, 1.0f);
}
void UEnemyAnimInstance::PlayRushAttackMontage()
{
	Montage_Play(RushAttackMontage, 1.0f);
}