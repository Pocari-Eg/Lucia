// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

UMyAnimInstance::UMyAnimInstance()
{
	AttackCount = 0;
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if(::IsValid(Pawn))
	{
		C = Cast<AIreneCharacter>(this->TryGetPawnOwner());
		AttackCount = C->GetAttackCountAnim();
	}
}