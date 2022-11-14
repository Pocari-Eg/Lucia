// Fill out your copyright notice in the Description page of Project Settings.


#include "BfSoundInstance.h"

UBfSoundInstance::UBfSoundInstance()
{
	BfProjectileEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_BFProjectile");
	BfRushAttackEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Enemy/BF/SFX_BFRushAttack");
}

void UBfSoundInstance::Init()
{
	BfProjectile = new SoundManager(BfProjectileEvent, GetWorld());
	BfProjectile->SetVolume(1.0f);

	BfRushAttack = new SoundManager(BfRushAttackEvent, GetWorld());
	BfRushAttack->SetVolume(1.0f);
}

void UBfSoundInstance::PlayBfProjectile(FTransform Transform)
{
	BfProjectile->SoundPlay3D(Transform);
}

void UBfSoundInstance::PlayBfRushAttack(FTransform Transform)
{
	BfRushAttack->SoundPlay3D(Transform);
}



