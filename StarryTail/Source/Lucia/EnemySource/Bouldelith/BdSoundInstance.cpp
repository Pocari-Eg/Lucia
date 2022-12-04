// Fill out your copyright notice in the Description page of Project Settings.


#include "BdSoundInstance.h"


UBdSoundInstance::UBdSoundInstance()
{
	BDAttackEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_BDAttack");
	BDQuakeEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_BDQuake");
	BDDeathEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_Death");
	BDGroggyEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_Groggy");
	BDRushEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BD/SFX_Rush");
}

void UBdSoundInstance::Init()
{
	BDAttack = new SoundManager(BDAttackEvent, GetWorld());
	BDAttack->SetVolume(1.0f);

	BDQuake = new SoundManager(BDQuakeEvent, GetWorld());
	BDQuake->SetVolume(1.0f);


	BDDeath = new SoundManager(BDDeathEvent, GetWorld());
	BDDeath->SetVolume(1.0f);


	BDGroggy = new SoundManager(BDGroggyEvent, GetWorld());
	BDGroggy->SetVolume(1.0f);


	BDRush = new SoundManager(BDRushEvent, GetWorld());
	BDRush->SetVolume(1.0f);
}

void UBdSoundInstance::PlayBDAttackSound(FTransform Transform)
{
	BDAttack->SoundPlay3D(Transform);
}

void UBdSoundInstance::PlayBDQuakeSound(FTransform Transform)
{
	BDQuake->SoundPlay3D(Transform);
}

void UBdSoundInstance::PlayBDDeathSound(FTransform Transform)
{
	BDDeath->SoundPlay3D(Transform);
}

void UBdSoundInstance::PlayBDGroggySound(FTransform Transform)
{
	BDGroggy->SoundPlay3D(Transform);
}

void UBdSoundInstance::PlayBDRushSound(FTransform Transform)
{
	BDRush->SoundPlay3D(Transform);
}
