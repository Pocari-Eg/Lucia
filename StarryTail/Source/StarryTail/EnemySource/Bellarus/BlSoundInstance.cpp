// Fill out your copyright notice in the Description page of Project Settings.


#include "BlSoundInstance.h"

UBlSoundInstance::UBlSoundInstance()
{
	WingEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BLAttack");
	DeathEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_Death");
	GroggyEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_Groggy");
}

void UBlSoundInstance::Init()
{
	WingSound = new SoundManager(WingEvent, GetWorld());
	WingSound->SetVolume(1.0f);

	Death = new SoundManager(DeathEvent, GetWorld());
	Death->SetVolume(1.0f);

	Groggy = new SoundManager(GroggyEvent, GetWorld());
	Groggy->SetVolume(1.0f);
}

void UBlSoundInstance::PlayWingSound(FTransform Transform)
{

	WingSound->SoundPlay3D(Transform);
}

void UBlSoundInstance::PlayDeathSound(FTransform Transform)
{
	Death->SoundPlay3D(Transform);

}

void UBlSoundInstance::PlayGroggySound(FTransform Transform)
{
	Groggy->SoundPlay3D(Transform);

}




