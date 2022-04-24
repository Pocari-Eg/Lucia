// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../UI/PlayerHudWidget.h"
#include "../SoundManager.h"

#include "IreneUIManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMpChangeDelegate);

UCLASS()
class STARRYTAIL_API UIreneUIManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	class AIreneCharacter* Irene;
public:
	// 로그 출력용
	bool bShowLog;
	
	FOnHpChangeDelegate OnHpChanged;
	FOnMpChangeDelegate OnMpChanged;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UPlayerHudWidget> PlayerHudClass;   // 위젯 클래스 
	UPROPERTY()
	class UPlayerHudWidget* PlayerHud; // 위젯
	
	//사운드 이벤트
	UPROPERTY(EditAnyWhere,Category="SOUND_VOLUME",meta=(ClampMin="0", ClampMax = "1"))
	float WalkSoundVolume;
	class UFMODEvent* AttackEvent;
	class UFMODEvent* WalkEvent;
	//사운드 
	SoundManager* WalkSound;
	SoundManager* AttackSound;

	float AttackSoundParameter;
private:
	UIreneUIManager();
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	void Begin();
	
	//현재 체력 비율 전환
	float GetHpRatio();
	//현재 마나 비율 전환
	float GetMpRatio();

	//사운드 출력
	void FootStepSound();
};
