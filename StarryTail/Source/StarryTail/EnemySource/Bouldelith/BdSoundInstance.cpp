// Fill out your copyright notice in the Description page of Project Settings.


#include "BdSoundInstance.h"

UBdSoundInstance::UBdSoundInstance()
{
	BDAttackEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_BDAttack");
	BDQuakeEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_BDQuake");
}

void UBdSoundInstance::Init()
{
	BDAttack = new SoundManager(BDAttackEvent, GetWorld());
	BDAttack->SetVolume(1.0f);

	BDQuake = new SoundManager(BDQuakeEvent, GetWorld());
	BDQuake->SetVolume(1.0f);
}

void UBdSoundInstance::PlayBDAttackSound(FTransform Transform)
{
	BDAttack->SoundPlay3D(Transform);
}

void UBdSoundInstance::PlayBDQuakeSound(FTransform Transform)
{
	BDQuake->SoundPlay3D(Transform);
}
