// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneSoundInstance.h"
#include"../IreneCharacter.h"
UIreneSoundInstance::UIreneSoundInstance()
{

	//hit Sound
	WalkEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_FootStep");
	AttackEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_Attack");
	AttackVoiceEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/Voice/SFX_AttackVoice");
	TakeDamageVoiceEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/Voice/SFX_TakeDamageVoice");

	DodgeEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_Dodge");
	StanceChangeEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_StanceChange");
	UltimateEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_Ultimate");
	SkillVocieEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/Voice/SFX_SkillVoice");

	StackBreakSlashEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_StackBreakSlash");
	StackBreakMoveEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_StackBreakMove");
}

void UIreneSoundInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);

	AttackSound = new SoundManager(AttackEvent, GetWorld());
	WalkSound = new SoundManager(WalkEvent, GetWorld());
	AttackVoiceSound = new SoundManager(AttackVoiceEvent, GetWorld());
	TakeDamageVoiceSound = new SoundManager(TakeDamageVoiceEvent, GetWorld());


	DodgeSound = new SoundManager(DodgeEvent, GetWorld());
	StanceChangeSound = new SoundManager(StanceChangeEvent, GetWorld());
	UltimateSound = new SoundManager(UltimateEvent, GetWorld());
	SkillVocieSound = new SoundManager(SkillVocieEvent, GetWorld());

	StackBreakMoveSound = new SoundManager(StackBreakMoveEvent, GetWorld());
	StackBreakSlashSound = new SoundManager(StackBreakSlashEvent, GetWorld());

	//사운드 세팅
	WalkSound->SetVolume(0.7f);
	WalkSound->SetParameter("Material", 0.0f);
	AttackSound->SetVolume(0.3f);
	AttackVoiceSound->SetVolume(0.3f);
	TakeDamageVoiceSound->SetVolume(0.4f);
	DodgeSound->SetVolume(0.3f);
	StanceChangeSound->SetVolume(0.3f);
	UltimateSound->SetVolume(0.3f);
	SkillVocieSound->SetVolume(0.3f);

	StackBreakMoveSound->SetVolume(1.0f);
	StackBreakSlashSound->SetVolume(1.0f);
}

void UIreneSoundInstance::PlayWalkSound()
{
	WalkSound->SoundPlay3D(Irene->GetActorTransform());
}

void UIreneSoundInstance::PlayAttackSound(float Param)
{

	AttackSound->SetParameter("StanceState", Param);

	AttackSound->SoundPlay2D();
	AttackVoiceSound->SoundPlay2D();
}


void UIreneSoundInstance::PlayTakeDamageVoiceSound()
{
	TakeDamageVoiceSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayDodgeSound(float Param)
{
	DodgeSound->SetParameter("DodgeType", Param);
	DodgeSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayStanceChangeSound(float Param)
{
	StanceChangeSound->SetParameter("StanceState", Param);
	StanceChangeSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayUltimateSound()
{
	UltimateSound->SoundPlay2D();
}

void UIreneSoundInstance::PlaySkillVoiceSound()
{
	SkillVocieSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayStackBreakSlash(FTransform transform)
{
	StackBreakSlashSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayStackBreakMove(FTransform transform)
{
	StackBreakMoveSound->SoundPlay2D();
}

void UIreneSoundInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}


