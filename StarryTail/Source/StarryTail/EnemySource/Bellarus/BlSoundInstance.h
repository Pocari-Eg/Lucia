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
	class UFMODEvent* HitEvent;
	SoundManager* BDAttack;
	class UFMODEvent* ShieldCrash;
	SoundManager* BDQuake;

public:

	UBlSoundInstance();

	void Init();
	void PlayBDAttackSound(FTransform Transform);
	void PlayBDQuakeSound(FTransform Transform);


	
};
