// Fill out your copyright notice in the Description page of Project Settings.


#include "BlSoundInstance.h"



UBlSoundInstance::UBlSoundInstance()
{
	WingEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BLAttack");
	DeathEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_Death");
	GroggyEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_Groggy");

	ShootProjectileEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BL_Projectile");
	TailEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BL_Tail");
	TelePortStartEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BL_TeleportSign");
	TelePortEndEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BL/SFX_BL_TeleportAttack");
}

void UBlSoundInstance::Init()
{
	WingSound = new SoundManager(WingEvent, GetWorld());
	WingSound->SetVolume(1.0f);

	Death = new SoundManager(DeathEvent, GetWorld());
	Death->SetVolume(1.0f);

	Groggy = new SoundManager(GroggyEvent, GetWorld());
	Groggy->SetVolume(1.0f);

	ShootProjectileSound = new SoundManager(ShootProjectileEvent, GetWorld());
	ShootProjectileSound->SetVolume(1.0f);

	TailSound = new SoundManager(TailEvent, GetWorld());
	TailSound->SetVolume(1.0f);

	TelePortStartSound = new SoundManager(TelePortStartEvent, GetWorld());
	TelePortStartSound->SetVolume(1.0f);

	TelePortEndSound = new SoundManager(TelePortEndEvent, GetWorld());
	TelePortEndSound->SetVolume(1.0f);
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

void UBlSoundInstance::PlayTailSound(FTransform Transform)
{
	TailSound->SoundPlay3D(Transform);
}

void UBlSoundInstance::PlayShootSound(FTransform Transform)
{
	ShootProjectileSound->SoundPlay3D(Transform);
}

void UBlSoundInstance::PlayTelePortStartSound(FTransform Transform)
{
	TelePortStartSound->SoundPlay3D(Transform);
}

void UBlSoundInstance::PlayTelePortEndSound(FTransform Transform)
{
	TelePortEndSound->SoundPlay3D(Transform);
}




