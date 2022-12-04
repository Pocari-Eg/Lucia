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
	SpiritSkillVoiceEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/Voice/SFX_SpiritSkillVoice");
	SpiritSkillEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_SpiritAttack");

	StackBreakSlashEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_StackBreakSlash");
	StackBreakMoveEvent = UFMODBlueprintStatics::FindEventByName("event:/Lucia/Irene/SFX_StackBreakMove");

	OptionEvent = UFMODBlueprintStatics::FindEventByName("event:/UI/SFX_Option");
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

	SpiritSkillVoiceSound = new SoundManager(SpiritSkillVoiceEvent, GetWorld());
	SpiritSkillSound = new SoundManager(SpiritSkillEvent, GetWorld());

	StackBreakMoveSound = new SoundManager(StackBreakMoveEvent, GetWorld());
	StackBreakSlashSound = new SoundManager(StackBreakSlashEvent, GetWorld());

	OptionSound = new SoundManager(OptionEvent, GetWorld());


	//사운드 세팅
	WalkSound->SetVolume(1.0f);
	WalkSound->SetParameter("Material", 0.0f);
	AttackSound->SetVolume(0.5f);
	AttackVoiceSound->SetVolume(0.4f);
	TakeDamageVoiceSound->SetVolume(0.5f);
	DodgeSound->SetVolume(0.5f);
	StanceChangeSound->SetVolume(0.5f);
	UltimateSound->SetVolume(0.5f);

	SpiritSkillVoiceSound->SetVolume(0.4f);
	SpiritSkillSound->SetVolume(0.7f);

	StackBreakMoveSound->SetVolume(1.0f);
	StackBreakSlashSound->SetVolume(1.0f);
	OptionSound->SetVolume(1.0f);
}

void UIreneSoundInstance::PlayWalkSound()
{
	WalkSound->SoundPlay3D(Irene->GetActorTransform());
}

void UIreneSoundInstance::PlayAttackSound(float Param)
{

	AttackSound->SetParameter("StanceState", Param);

	AttackSound->SoundPlay2D();

	AttackVoiceSound->SetParameter("AttackType", AttackSoundType);
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

void UIreneSoundInstance::PlaySpiritSkillSound()
{
	SpiritSkillVoiceSound->SoundPlay2D();

	SpiritSkillSound->SetParameter("AttackType", SpiritSkillSoundType);
	SpiritSkillSound->SoundPlay2D();
}
void UIreneSoundInstance::PlayStackBreakSlash(FTransform transform)
{
	StackBreakSlashSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayStackBreakMove(FTransform transform)
{
	StackBreakMoveSound->SoundPlay2D();
}

void UIreneSoundInstance::PlayOptionSound()
{
	STARRYLOG_S(Error);
	OptionSound->SoundPlay2D();
}

void UIreneSoundInstance::SetAttackSoundType(float Type)
{
	AttackSoundType = Type;
}

void UIreneSoundInstance::SetSpiritSkillSoundType(float Type)
{
	SpiritSkillSoundType = Type;
}

void UIreneSoundInstance::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}


