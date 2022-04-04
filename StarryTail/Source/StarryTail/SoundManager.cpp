// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::SoundPlay3D(FTransform transform)
{
	//���尡 �ܹ߼��� ��� �Ź� �ν��Ͻ��� ������ٰ� ���尡 ����Ǹ� �ν��Ͻ��� ��������.
	//���尡 �������̸� Relesase���� �ʴ��̻� ���尡 ��� ��� �Ǹ鼭 �ν��Ͻ��� ��������
	//�ν��Ͻ��� �����־�� ������ ���� ���� �����ϹǷ� �ܹ߼��� ��� ���尡 ��µǱ��� ���� �����Ų�� ���
	//���尡 �������ϰ�� ���� ��µ��� ���带 ���� ���� 
	
	if (Event != nullptr) {
		//���� �ν��Ͻ��� ���� 
		Instance = UFMODBlueprintStatics::PlayEventAtLocation(World, Event, transform, false);
		
		char* result = TCHAR_TO_ANSI(*Parameter);
		Instance.Instance->setParameterByName(result, ParameterValue);
		//���� ���� ����
		Instance.Instance->setVolume(Volume);
		//���� �÷���
		UFMODBlueprintStatics::EventInstancePlay(Instance);
	}
}

void SoundManager::SoundPlay2D()
{
	if (Event != nullptr) {

		Instance = UFMODBlueprintStatics::PlayEvent2D(World, Event, false);
		char* result = TCHAR_TO_ANSI(*Parameter);
		Instance.Instance->setParameterByName(result, ParameterValue);
		Instance.Instance->setVolume(Volume);
		UFMODBlueprintStatics::EventInstancePlay(Instance);
		
	}
}

void SoundManager::SoundStop()
{
	if (Event != nullptr) {
		//���� ����
		Instance.Instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);//FadeOut����
		Instance.Instance->release();
	}
}

void SoundManager::SetTransform(FTransform transform)
{
	if (Event != nullptr) {
		//���尡 ��Ÿ���� ��ġ ����
		UFMODBlueprintStatics::EventInstanceSetTransform(Instance, transform);
	}
}

void SoundManager::SetVolume(float Vol)
{
	if (Event != nullptr) {
		//������ ���� ����

	//���尡 �ܹ߼��̸� ���� �����ߴٰ� ���� ���� ��¶� ���asdB
		Volume = Vol;
		//���尡 �������̸� �������ٷ� ����
		if (Instance.Instance->isValid()) {
			UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
		}
	}
}

void SoundManager::SetParameter(FString parameter, float Value)
{
	if (Event != nullptr) {
		//������ �Ķ���Ͱ� ����
		//���尡 �ܹ߼��̸� ���� �����ߴٰ� ���� ���� ��¶� ���
		this->Parameter = parameter;
		this->ParameterValue = Value;		
	
	}
}

void SoundManager::PlayingChangeParamter(FString parameter, float Value)
{
	if (Instance.Instance->isValid()) {

		UFMODBlueprintStatics::EventInstanceSetParameter(Instance, FName(parameter), Value);
	}
}
