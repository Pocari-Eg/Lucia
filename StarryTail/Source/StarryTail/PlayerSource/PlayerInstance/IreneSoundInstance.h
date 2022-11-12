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
	//���� �̺�Ʈ
	class UFMODEvent* AttackEvent;
	class UFMODEvent* WalkEvent;


	class UFMODEvent* DodgeEvent;
	class UFMODEvent* StanceChangeEvent;
	class UFMODEvent* UltimateEvent;


	//voice
	class UFMODEvent* AttackVoiceEvent;
	class UFMODEvent* TakeDamageVoiceEvent;
	class UFMODEvent* SkillVocieEvent;


	//���� 
	SoundManager* AttackSound;
	SoundManager* AttackVoiceSound;
	//
	SoundManager* WalkSound;
	SoundManager* DodgeSound;
	SoundManager* StanceChangeSound;
	SoundManager* UltimateSound;
	//voice 

	SoundManager* TakeDamageVoiceSound;
	SoundManager* SkillVocieSound;

	UPROPERTY()
		class AIreneCharacter* Irene;
#pragma endregion Sound
public:

	UIreneSoundInstance();

	void Init(AIreneCharacter* Value);

	void PlayWalkSound();
	void PlayAttackSound(float Param);
	void PlayTakeDamageVoiceSound();

	void PlayDodgeSound(float Param);
	void PlayStanceChangeSound(float Param);
	void PlayUltimateSound();
	void PlaySkillVoiceSound();

private:
	void SetIreneCharacter(AIreneCharacter* Value);
};
