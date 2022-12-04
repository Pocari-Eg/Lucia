// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundPlayer.h"

// Sets default values
ASoundPlayer::ASoundPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASoundPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ASoundPlayer::PlayBGM()
{
	Sound = new SoundManager(Event, GetWorld());
	Sound->SetVolume(Volume);
	Sound->SoundPlay2D();
}

void ASoundPlayer::PlayAMB()
{

	Sound = new SoundManager(Event, GetWorld());
	Sound->SetVolume(Volume);
	Sound->SoundPlay3D(this->GetTransform());
}

ESoundStyle ASoundPlayer::GetSoundType()
{
	return Type;
}

void ASoundPlayer::ChangeBgm(float Param)
{
	Sound->PlayingChangeParamter("Stage", Param);
}




