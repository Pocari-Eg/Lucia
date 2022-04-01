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

		Parameter = FName("Empty");
		ParameterValue = 0.0f;
		Volume = 1.0f;
	}
	~SoundManager();
private:
	UWorld* World;
	UFMODEvent* Event;
	FFMODEventInstance Instance;

	FName Parameter;
	float ParameterValue;

	float Volume;
public:
	//�ش� ��ġ���� ���� �÷���
	void SoundPlay3D(FTransform transform);

	//2D���� �÷��� 
	void SoundPlay2D();
	//���� ����
	void SoundStop();

	//���� ��ġ ����
	void SetTransform(FTransform transform);

	//���� ���� ����
	void SetVolume(float Vol);

	//�Ķ���� ����
	void SetParameter(FString  parameter, float Value);
};
