// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSoundInstance.h"

UMonsterSoundInstance::UMonsterSoundInstance()
{

	//hit Sound
	HitEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Enemy/SFX_Hit");
	ShieldCrash = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Enemy/SFX_ManaShieldCrash");
}

void UMonsterSoundInstance::Init()
{
	HitSound = new SoundManager(HitEvent, GetWorld());
	HitSound->SetVolume(1.0f);

	ShieldCrashSound = new SoundManager(ShieldCrash, GetWorld());
	ShieldCrashSound->SetVolume(0.1f);
}

void UMonsterSoundInstance::PlayHitSound(FTransform Transform)
{
	HitSound->SoundPlay3D(Transform);
}

void UMonsterSoundInstance::SetHitSound(FString Path)
{
	HitEvent = UFMODBlueprintStatics::FindEventByName(Path);
	HitSound = new SoundManager(HitEvent, GetWorld());
}

void UMonsterSoundInstance::PlayShieldCrashSound()
{
	ShieldCrashSound->SoundPlay2D();
}

SoundManager* UMonsterSoundInstance::GetHitSound()
{
	return HitSound;
}

SoundManager* UMonsterSoundInstance::GetShieldCrashSound()
{
	return ShieldCrashSound;
}
