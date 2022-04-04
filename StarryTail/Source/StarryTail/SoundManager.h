// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include <FMODBlueprintStatics.h>
/**
 * 
 */
class STARRYTAIL_API SoundManager
{
public:
	SoundManager();
	SoundManager(UFMODEvent* Event, UWorld* World) {
		this->Event = Event;
		this->World = World;

		
		ParameterValue = 0.0f;
		Volume = 1.0f;
	}
	~SoundManager();
private:
	UWorld* World;
	UFMODEvent* Event;
	FFMODEventInstance Instance;

	FString Parameter = "Empty";
	float ParameterValue;
	float CurrentParameterValue=-1.0f;
	float Volume;
public:
	//해당 위치에서 사운드 플레이
	void SoundPlay3D(FTransform transform);

	//2D사운드 플레이 
	void SoundPlay2D();
	//사운드 멈춤
	void SoundStop();

	//사운드 위치 변경
	void SetTransform(FTransform transform);

	//사운드 볼륨 변경
	void SetVolume(float Vol);

	//파라미터 변경
	void SetParameter(FString  parameter, float Value);
	void PlayingChangeParamter(FString  parameter, float Value);

};
