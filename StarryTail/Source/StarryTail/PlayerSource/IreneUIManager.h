// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../UI/PlayerHudWidget.h"
#include "../SoundManager.h"
#include "PlayerCharacterDataStruct.h"

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

	//현재 회복 대기 시간
	int CurRecoverWaitTime;
	//현재 회복 시간
	int CurRecoverTime;
	//남은 회복량
	int RemainingRecovry;
	//타이머 핸들
	FTimerHandle HpRecorveryTimerHandle;
	FTimerHandle HpRecorveryWaitTimerHandle;
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

	//회복 대기 관련

	//회복 대기 기다림
	void HPRecoveryWaiting();

	//회복 관련

	//회복 중
	void HPRecovering();

	//Hp 확인
	bool IsHpFull();
	
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	void Begin();

	//회복 대기 시작
	void HPRecoveryWaitStart();
	//회보 대기 취소
	void HPRecoveryWaitCancel();
	//회복 시작
	void HPRecoveringStart();
	//회복 취소
	void HpRecoveringCancel();
	
	//현재 체력 비율 전환
	float GetHpRatio();
	//현재 마나 비율 전환
	float GetMpRatio();

	//사운드 출력
	void FootStepSound();
	
	//Hp RecoveryBar 
	float GetHpRecoveryRatio();
};
