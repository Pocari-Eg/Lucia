// Fill out your copyright notice in the Description page of Project Settings.


#include "BfSoundInstance.h"

UBfSoundInstance::UBfSoundInstance()
{
	BfProjectileEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_BFProjectile");
	BfRushAttackEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_BFRushAttack");
	DeathEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_Death");
	GroggyEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_Groggy");
	RangeAttackEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_RangeAttack");

}

void UBfSoundInstance::Init()
{
	BfProjectile = new SoundManager(BfProjectileEvent, GetWorld());
	BfProjectile->SetVolume(1.0f);

	BfRushAttack = new SoundManager(BfRushAttackEvent, GetWorld());
	BfRushAttack->SetVolume(1.0f);

	Death = new SoundManager(DeathEvent, GetWorld());
	Death->SetVolume(1.0f);

	Groggy = new SoundManager(GroggyEvent, GetWorld());
	Groggy->SetVolume(1.0f);

	RangeAttack = new SoundManager(RangeAttackEvent, GetWorld());
	RangeAttack->SetVolume(1.0f);
}

void UBfSoundInstance::PlayBfProjectile(FTransform Transform)
{
	BfProjectile->SoundPlay3D(Transform);
}

void UBfSoundInstance::PlayBfRushAttack(FTransform Transform)
{
	BfRushAttack->SoundPlay3D(Transform);
}

void UBfSoundInstance::PlayDeathSound(FTransform Transform)
{
	Death->SoundPlay3D(Transform);
}

void UBfSoundInstance::PlayGroggySound(FTransform Transform)
{
	Groggy->SoundPlay3D(Transform);
}

void UBfSoundInstance::PlayRangeAttackSound(FTransform Transform)
{
	RangeAttack->SoundPlay3D(Transform);
}



