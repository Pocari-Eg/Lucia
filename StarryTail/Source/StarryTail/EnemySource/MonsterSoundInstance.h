// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Sound/SoundManager.h"
#include "MonsterSoundInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UMonsterSoundInstance : public UObject
{
	GENERATED_BODY()
private:
	class UFMODEvent* HitEvent;
	SoundManager* HitSound;
	class UFMODEvent* ShieldCrash;
	SoundManager* ShieldCrashSound;
	class UFMODEvent* ShieldHit;
	SoundManager* ShieldHitSound;

	class UFMODEvent* StackExplosion;
	SoundManager* StackExplosionSound;
public:

	UMonsterSoundInstance();

	void Init();
	void PlayHitSound(FTransform Transform, float Param);
	void SetHitSound(FString Path);

	void PlayShieldDestroySound(FTransform Transform);
	void PlayShieldHitSound(FTransform Transform);

	void PlayStackExplosionSound(FTransform Transform);

	SoundManager* GetHitSound();
	SoundManager* GetShieldCrashSound();
};
