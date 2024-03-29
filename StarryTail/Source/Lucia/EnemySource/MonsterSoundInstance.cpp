// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSoundInstance.h"

UMonsterSoundInstance::UMonsterSoundInstance()
{

	//hit Sound
	HitEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/SFX_Hit");
	ShieldCrash = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/SFX_ShieldDestroy");
	ShieldHit = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/SFX_ShieldHit");
	StackExplosion = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_StackExplosion");
}


class UFMODEvent* StackExplosion;
SoundManager* StackExplosionSound;
void UMonsterSoundInstance::Init()
{
	HitSound = new SoundManager(HitEvent, GetWorld());
	HitSound->SetVolume(1.0f);

	ShieldCrashSound = new SoundManager(ShieldCrash, GetWorld());
	ShieldCrashSound->SetVolume(1.0f);

	ShieldHitSound = new SoundManager(ShieldHit, GetWorld());
	ShieldHitSound->SetVolume(1.0f);

	StackExplosionSound = new SoundManager(StackExplosion, GetWorld());
	StackExplosionSound->SetVolume(1.0f);
}

void UMonsterSoundInstance::PlayHitSound(FTransform Transform,float Param)
{
	HitSound->SetParameter("Monster", Param);
	HitSound->SoundPlay3D(Transform);
}

void UMonsterSoundInstance::SetHitSound(FString Path)
{
	HitEvent = UFMODBlueprintStatics::FindEventByName(Path);
	HitSound = new SoundManager(HitEvent, GetWorld());
}

void UMonsterSoundInstance::PlayShieldDestroySound(FTransform Transform)
{
	ShieldCrashSound->SoundPlay3D(Transform);
}

void UMonsterSoundInstance::PlayShieldHitSound(FTransform Transform)
{
	ShieldHitSound->SoundPlay3D(Transform);
}

void UMonsterSoundInstance::PlayStackExplosionSound(FTransform Transform)
{
	StackExplosionSound->SoundPlay3D(Transform);
}

SoundManager* UMonsterSoundInstance::GetHitSound()
{
	return HitSound;
}

SoundManager* UMonsterSoundInstance::GetShieldCrashSound()
{
	return ShieldCrashSound;
}
