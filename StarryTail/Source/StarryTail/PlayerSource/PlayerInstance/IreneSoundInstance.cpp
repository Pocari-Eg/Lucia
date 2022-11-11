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
}

void UIreneSoundInstance::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);

	AttackSound = new SoundManager(AttackEvent, GetWorld());
	WalkSound = new SoundManager(WalkEvent, GetWorld());
	AttackVoiceSound = new SoundManager(AttackVoiceEvent, GetWorld());
	TakeDamageVoiceSound = new SoundManager(TakeDamageVoiceEvent, GetWorld());

	//사운드 세팅
	WalkSound->SetVolume(0.7f);
	WalkSound->SetParameter("Material", 0.0f);

	AttackSound->SetVolume(0.3f);

	AttackVoiceSound->SetVolume(0.3f);

	TakeDamageVoiceSound->SetVolume(0.4f);
}

void UIreneSoundInstance::PlayWalkSound()
{
	WalkSound->SoundPlay3D(Irene->GetActorTransform());
}

void UIreneSoundInstance::PlayAttackSound()
{
	AttackSound->SoundPlay2D();
	AttackVoiceSound->SoundPlay2D();
}


void UIreneSoundInstance::PlayTakeDamageVoiceSound()
{
	TakeDamageVoiceSound->SoundPlay2D();
}

void UIreneSoundInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}


