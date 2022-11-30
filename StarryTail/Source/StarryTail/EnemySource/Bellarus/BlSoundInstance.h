// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSoundInstance.h"
#include "BlSoundInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBlSoundInstance : public UMonsterSoundInstance
{
	GENERATED_BODY()
	private:
	class UFMODEvent* WingEvent;
	SoundManager* WingSound;
	class UFMODEvent* DeathEvent;
	SoundManager* Death;
	class UFMODEvent* GroggyEvent;
	SoundManager* Groggy;

	class UFMODEvent* ShootProjectileEvent;
	SoundManager* ShootProjectileSound;

	class UFMODEvent* TailEvent;
	SoundManager* TailSound;



	class UFMODEvent* TelePortStartEvent;
	SoundManager* TelePortStartSound;


	class UFMODEvent* TelePortEndEvent;
	SoundManager* TelePortEndSound;

public:

	UBlSoundInstance();

	void Init();
	void PlayWingSound(FTransform Transform);
	void PlayDeathSound(FTransform Transform);
	void PlayGroggySound(FTransform Transform);
	void PlayTailSound(FTransform Transform);
	void PlayShootSound(FTransform Transform);

	void PlayTelePortStartSound(FTransform Transform);
	void PlayTelePortEndSound(FTransform Transform);
};
