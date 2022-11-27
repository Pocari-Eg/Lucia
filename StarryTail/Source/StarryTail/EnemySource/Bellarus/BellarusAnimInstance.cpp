// Fill out your copyright notice in the Description page of Project Settings.


#include "BellarusAnimInstance.h"
#include "Bellarus.h"
#include "BlSoundInstance.h"


void UBellarusAnimInstance::PlayIdleMontage()
{

		if (Montage_IsPlaying(IdleMontage))
			return;


			Montage_Play(IdleMontage, PlayRate);
}

void UBellarusAnimInstance::PlayDeathMontage()
{
	Montage_Play(DeathMontage);
}



void UBellarusAnimInstance::PlayDetectMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
	Montage_Play(DetectMontage, 1.0f);
}

void UBellarusAnimInstance::PlayAttackedMontage()
{
	if (CheckAttackedMontagePlaying())
		return;
		Montage_Play(AttackedMontage, 1.0f);
}

void UBellarusAnimInstance::PlayWalkMontage()
{
	if (Montage_IsPlaying(WalkMontage))
		return;

		Montage_Play(WalkMontage, PlayRate);
}




void UBellarusAnimInstance::PlayWingLMontage()
{

	Montage_Play(WingLMontage, 1.0f);
}

void UBellarusAnimInstance::PlayWingRMontage()
{

	Montage_Play(WingRMontage, 1.0f);
}

void UBellarusAnimInstance::PlayTailMontage()
{

	Montage_Play(TailMontage, 1.0f);
}

void UBellarusAnimInstance::PlaySwirlMontage()
{
	Montage_Play(SwirlMontage, 1.0f);

}

void UBellarusAnimInstance::PlayFeatherMontage()
{
	Montage_Play(FeatherMontage, 1.0f);

}

void UBellarusAnimInstance::PlayStartTelePortMontage()
{
	Montage_Play(TelePortStartMontage, 1.0f);
}

void UBellarusAnimInstance::PlayEndTelePortMontage()
{
	Montage_Play(TelePortEndMontage, 1.0f);
}



void UBellarusAnimInstance::AnimNotify_Tail()
{
	TailAttack.Broadcast();
}

void UBellarusAnimInstance::AnimNotify_WingL()
{
	WingLAttack.Broadcast();
}

void UBellarusAnimInstance::AnimNotify_WingR()
{
	WingRAttack.Broadcast();
}

void UBellarusAnimInstance::AnimNotify_Swirl()
{
	SwirlAttack.Broadcast();
}

void UBellarusAnimInstance::AnimNotify_Feather()
{
	FeatherAttack.Broadcast();
}

void UBellarusAnimInstance::AnimNotify_TelePort()
{
	TelePortAttack.Broadcast();
}

void UBellarusAnimInstance::AnimNotify_DeathSound()
{
	Bellarus->GetBlSound()->PlayDeathSound(Bellarus->GetTransform());
}

void UBellarusAnimInstance::AnimNotify_GroggySound()
{
	Bellarus->GetBlSound()->PlayGroggySound(Bellarus->GetTransform());
}

void UBellarusAnimInstance::AnimNotify_WingSound()
{
	Bellarus->GetBlSound()->PlayWingSound(Bellarus->GetTransform());
}

void UBellarusAnimInstance::Init(ABellarus* Value)
{
	Bellarus = Value;
}

bool UBellarusAnimInstance::CheckAttackedMontagePlaying()
{
	//맞는 중 애니메이션 실행 중인지
	if (Montage_IsPlaying(AttackedMontage))
		return true;

	return false;
}
