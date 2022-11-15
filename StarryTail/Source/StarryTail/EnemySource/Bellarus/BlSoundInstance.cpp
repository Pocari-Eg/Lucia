// Fill out your copyright notice in the Description page of Project Settings.


#include "BlSoundInstance.h"

UBlSoundInstance::UBlSoundInstance()
{
	WingEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BLAttack");
}

void UBlSoundInstance::Init()
{
	WingSound = new SoundManager(WingEvent, GetWorld());
	WingSound->SetVolume(1.0f);
}

void UBlSoundInstance::PlayWingSound(FTransform Transform)
{

	WingSound->SoundPlay3D(Transform);
}




