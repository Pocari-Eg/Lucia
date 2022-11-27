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


	class UFMODEvent* DodgeEvent;
	class UFMODEvent* StanceChangeEvent;
	class UFMODEvent* UltimateEvent;


	//voice
	class UFMODEvent* AttackVoiceEvent;
	class UFMODEvent* TakeDamageVoiceEvent;
	class UFMODEvent* SkillVocieEvent;
	class UFMODEvent* SkillVocie1Event;

	class UFMODEvent* DeathVoiceEvent;

	//StackBreak
	class UFMODEvent* StackBreakMoveEvent;
	class UFMODEvent* StackBreakSlashEvent;


	//ui
	
	class UFMODEvent* OptionEvent;

	//사운드 
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
	SoundManager* SkillVocie1Sound;
	SoundManager* DeathVoiceSound;


	//stackbreakl
	SoundManager* StackBreakMoveSound;
	SoundManager* StackBreakSlashSound;


	//ui
	SoundManager* OptionSound;


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
	void PlaySkillVoice1Sound();

	void PlayStackBreakSlash(FTransform transform);
	void PlayStackBreakMove(FTransform transform);


	void PlayOptionSound();
private:
	void SetIreneCharacter(AIreneCharacter* Value);
};
