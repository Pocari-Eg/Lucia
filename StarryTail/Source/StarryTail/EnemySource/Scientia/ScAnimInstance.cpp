// Fill out your copyright notice in the Description page of Project Settings.


#include "ScAnimInstance.h"

void UScAnimInstance::PlayFeatherRMontage()
{
	Montage_Play(FeatherMontageR);
}
void UScAnimInstance::PlayFeatherLMontage()
{
	Montage_Play(FeatherMontageL);
}
void UScAnimInstance::PlayFeatherMMontage()
{
	Montage_Play(FeatherMontageM);
}
void UScAnimInstance::PlayClawFMontage()
{
	Montage_Play(ClawFMontage);
}
void UScAnimInstance::PlayRushMontage()
{
	Montage_Play(RushMontage);
}
void UScAnimInstance::PlayStuckMontage()
{
	Montage_Play(StuckMontage);
}
void UScAnimInstance::PlayTurnMontage()
{
	Montage_Play(TurnMontage);
}
void UScAnimInstance::PlayChangeMontage()
{
	Montage_Play(ChangeMontage);
}
void UScAnimInstance::PlayDodgeMontage()
{
	Montage_Play(DodgeMontage);
}
void UScAnimInstance::PlayAttackedBAnimation()
{
	Montage_Play(AttackedBMontage);
}
void UScAnimInstance::PlayAttackedFAnimation()
{
	Montage_Play(AttackedFMontage);
}
void UScAnimInstance::PlayCrushedMontage()
{
	Montage_Play(CrushedMontage);
}
void UScAnimInstance::AnimNotify_Feather()
{
	Feather.Broadcast();
}

void UScAnimInstance::AnimNotify_AddFeatherCount()
{
	AddFeather.Broadcast();
}
void UScAnimInstance::AnimNotify_ClawStart()
{
	ClawStart.Broadcast();
}
void UScAnimInstance::AnimNotify_RushStart()
{
	RushStart.Broadcast();
}
void UScAnimInstance::AnimNotify_Attack1End()
{
	Attack1End.Broadcast();
}
void UScAnimInstance::AnimNotify_Attack2End()
{
	Attack2End.Broadcast();
}
void UScAnimInstance::AnimNotify_TurnEnd()
{
	TurnEnd.Broadcast();
}
void UScAnimInstance::AnimNotify_Change()
{
	Change.Broadcast();
}
void UScAnimInstance::AnimNotify_ChangeEnd()
{
	ChangeEnd.Broadcast();
}
void UScAnimInstance::AnimNotify_DodgeEnd()
{
	DodgeEnd.Broadcast();
}
void UScAnimInstance::AnimNotify_CrushedEnd()
{
	CrushedEnd.Broadcast();
}