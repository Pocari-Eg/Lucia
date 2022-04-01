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

	//���� �ν��Ͻ��� ���� 
	Instance = UFMODBlueprintStatics::PlayEventAtLocation(World, Event, transform, false);
	//������ �Ķ���Ͱ� �ش��ϴ� �Ķ���Ͱ� ������ �Ķ���� ����
	UFMODBlueprintStatics::EventInstanceSetParameter(Instance, Parameter, ParameterValue);
	//���� ���� ����
	UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
	//���� �÷���
	UFMODBlueprintStatics::EventInstancePlay(Instance);
}

void SoundManager::SoundPlay2D()
{
	
	Instance = UFMODBlueprintStatics::PlayEvent2D(World, Event, false);
	UFMODBlueprintStatics::EventInstanceSetParameter(Instance, Parameter, ParameterValue);
	UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
	UFMODBlueprintStatics::EventInstancePlay(Instance);


}

void SoundManager::SoundStop()
{
	//���� ����
	Instance.Instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);//FadeOut����
	Instance.Instance->release();
}

void SoundManager::SetTransform(FTransform transform)
{
	//���尡 ��Ÿ���� ��ġ ����
	UFMODBlueprintStatics::EventInstanceSetTransform(Instance, transform);
}

void SoundManager::SetVolume(float Vol)
{
	//������ ���� ����

//���尡 �ܹ߼��̸� ���� �����ߴٰ� ���� ���� ��¶� ���
	Volume = Vol;
	//���尡 �������̸� �������ٷ� ����
	if (Instance.Instance->isValid()) {
		UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
	}
}

void SoundManager::SetParameter(FString parameter, float Value)
{
	//������ �Ķ���Ͱ� ����
	//���尡 �ܹ߼��̸� ���� �����ߴٰ� ���� ���� ��¶� ���
	this->Parameter = FName(parameter);
	this->ParameterValue = Value;
	/*if (Instance.Instance->isValid()) {

		UFMODBlueprintStatics::EventInstanceSetParameter(Instance, Parameter, ParameterValue);
	}*/
}
