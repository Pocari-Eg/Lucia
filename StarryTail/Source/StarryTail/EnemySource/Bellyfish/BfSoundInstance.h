// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterSoundInstance.h"
#include "BfSoundInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBfSoundInstance : public UMonsterSoundInstance
{
	GENERATED_BODY()
	private:
	class UFMODEvent* BfProjectileEvent;
	SoundManager* BfProjectile;
	class UFMODEvent* BfRushAttackEvent;
	SoundManager* BfRushAttack;

public:

	UBfSoundInstance();

	void Init();
	void PlayBfProjectile(FTransform Transform);
	void PlayBfRushAttack(FTransform Transform);


	
};
