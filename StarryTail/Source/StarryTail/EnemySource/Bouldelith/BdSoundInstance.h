// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSoundInstance.h"
#include "BdSoundInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBdSoundInstance : public UMonsterSoundInstance
{
	GENERATED_BODY()
	private:
	class UFMODEvent* BDAttackEvent;
	SoundManager* BDAttack;
	class UFMODEvent* BDQuakeEvent;
	SoundManager* BDQuake;

public:

	UBdSoundInstance();

	void Init();
	void PlayBDAttackSound(FTransform Transform);
	void PlayBDQuakeSound(FTransform Transform);


	
};
