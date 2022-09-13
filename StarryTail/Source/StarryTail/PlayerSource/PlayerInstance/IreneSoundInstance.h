// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../../Sound/SoundManager.h"

#include "IreneSoundInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UIreneSoundInstance : public UObject
{
	GENERATED_BODY()
private:
#pragma region Sound
	//사운드 이벤트
	class UFMODEvent* AttackEvent;
	class UFMODEvent* WalkEvent;
	class UFMODEvent* AttackVoiceEvent;
	class UFMODEvent* TakeDamageVoiceEvent;
	//사운드 
	SoundManager* WalkSound;
	SoundManager* AttackSound;
	SoundManager* AttackVoiceSound;
	SoundManager* TakeDamageVoiceSound;

	UPROPERTY()
		class AIreneCharacter* Irene;
#pragma endregion Sound
public:

	UIreneSoundInstance();

	void Init(AIreneCharacter* Value);

	void PlayWalkSound();
	void PlayAttackSound();
	void PlayTakeDamageVoiceSound();

private:
	void SetIreneCharacter(AIreneCharacter* Value);
};
