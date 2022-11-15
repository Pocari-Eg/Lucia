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


public:

	UBlSoundInstance();

	void Init();
	void PlayWingSound(FTransform Transform);


	
};
