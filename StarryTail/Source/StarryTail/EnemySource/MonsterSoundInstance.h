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
public:

	UMonsterSoundInstance();

	void Init();
	void PlayHitSound(FTransform Transform);
	void SetHitSound(FString Path);

	void PlayShieldCrashSound();

	SoundManager* GetHitSound();
	SoundManager* GetShieldCrashSound();
};
