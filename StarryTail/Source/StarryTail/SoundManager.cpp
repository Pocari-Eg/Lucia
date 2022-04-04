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
	//사운드가 단발성인 경우 매번 인스턴스가 생성됬다가 사운드가 종료되면 인스턴스가 없어진다.
	//사운드가 연속적이면 Relesase하지 않는이상 사운드가 계속 출력 되면서 인스턴스가 남아있음
	//인스턴스가 남아있어야 사운드의 값을 변경 가능하므로 단발성일 경우 사운드가 출력되기전 값을 적용시킨후 출력
	//사운드가 연속적일경우 사운드 출력도중 사운드를 변경 가능 
	
	if (Event != nullptr) {
		//사운드 인스턴스를 만듬 
		Instance = UFMODBlueprintStatics::PlayEventAtLocation(World, Event, transform, false);
		
		char* result = TCHAR_TO_ANSI(*Parameter);
		Instance.Instance->setParameterByName(result, ParameterValue);
		//사운드 볼륨 조절
		Instance.Instance->setVolume(Volume);
		//사운드 플레이
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
		//사운드 종료
		Instance.Instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);//FadeOut종료
		Instance.Instance->release();
	}
}

void SoundManager::SetTransform(FTransform transform)
{
	if (Event != nullptr) {
		//사운드가 나타나는 위치 조절
		UFMODBlueprintStatics::EventInstanceSetTransform(Instance, transform);
	}
}

void SoundManager::SetVolume(float Vol)
{
	if (Event != nullptr) {
		//사운드의 볼륨 조절

	//사운드가 단발성이면 값을 저장했다가 다음 사운드 출력때 사용asdB
		Volume = Vol;
		//사운드가 연속적이면 볼륨을바로 조절
		if (Instance.Instance->isValid()) {
			UFMODBlueprintStatics::EventInstanceSetVolume(Instance, Volume);
		}
	}
}

void SoundManager::SetParameter(FString parameter, float Value)
{
	if (Event != nullptr) {
		//사운드의 파라미터값 설정
		//사운드가 단발성이면 값을 저장했다가 다음 사운드 출력때 사용
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
