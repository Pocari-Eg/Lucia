// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../UI/PlayerHudWidget.h"
#include"../UI/PauseWidget.h"
#include "../Sound/SoundManager.h"
#include "PlayerCharacterDataStruct.h"

#include "IreneUIManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnFireCoolChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnWaterCoolChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnThunderCoolChangeDelegate);

DECLARE_MULTICAST_DELEGATE(FOnFireSkillCoolChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnWaterSkillCoolChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnThunderSkillCoolChangeDelegate);
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
	int RemainingRecovery;
	//타이머 핸들
	FTimerHandle HpRecoveryTimerHandle;
	FTimerHandle HpRecoveryWaitTimerHandle;


	float FireMaxCoolTime;
	float FireCurCoolTime;

	float WaterMaxCoolTime;
	float WaterCurCoolTime;

	float ThunderMaxCoolTime;
	float ThunderCurCoolTime;



	float FireSkillMaxCoolTime;
	float FireSkillCurCoolTime;


	float WaterSkillMaxCoolTime;
	float WaterSkillCurCoolTime;


	float ThunderSkillMaxCoolTime;
	float ThunderSkillCurCoolTime;
public:
	// 로그 출력용
	bool bShowLog;
#pragma region HUD
	FOnHpChangeDelegate OnHpChanged;
	FOnMpChangeDelegate OnStaminaChanged;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UPlayerHudWidget> PlayerHudClass;   // 위젯 클래스 

	FOnFireCoolChangeDelegate OnFireCoolChange;
	FOnWaterCoolChangeDelegate OnWaterCoolChange;
	FOnThunderCoolChangeDelegate OnThunderCoolChange;

	FOnFireSkillCoolChangeDelegate OnFireSkillCoolChange;
	FOnWaterSkillCoolChangeDelegate OnWaterSkillCoolChange;
	FOnThunderSkillCoolChangeDelegate OnThunderSkillCoolChange;
public:

	UPROPERTY(BluePrintReadOnly, Category = UI)
	class UPlayerHudWidget* PlayerHud; // 위젯
#pragma endregion HUD

#pragma region PauseWidget
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
		TSubclassOf<class UPauseWidget> PauseWidgetClass;   // 위젯 클래스 
	UPROPERTY()
		class UPauseWidget* PauseWidget; // 위젯

	bool bIsOnPauseWidget;
#pragma endregion PauseWidget

#pragma region Sound
	//사운드 이벤트
	UPROPERTY(EditAnyWhere,Category="SOUND_VOLUME",meta=(ClampMin="0", ClampMax = "1"))
	float WalkSoundVolume;
	class UFMODEvent* AttackEvent;
	class UFMODEvent* WalkEvent;
	class UFMODEvent* AttackVoiceEvent;
	class UFMODEvent* JumpVoiceEvent;
	class UFMODEvent* TakeDamageVoiceEvent;
	class UFMODEvent* WaterDodgeEvent;
	class UFMODEvent* ThunderDodgeEvent;
	//사운드 
	SoundManager* WalkSound;
	SoundManager* AttackSound;
	SoundManager* AttackVoiceSound;
	SoundManager* JumpVoiceSound;
	SoundManager* TakeDamageVoiceSound;
	SoundManager* WaterDodgeSound;
	SoundManager* ThunderDodgeSound;

	float AttackSoundParameter;
#pragma endregion Sound
private:
	UIreneUIManager();
#pragma region HUDPrivate
	//회복 대기 관련

	//회복 대기 기다림
	void HPRecoveryWaiting();
	//회복 관련

	//회복 중
	void HPRecovering();

	//Hp 확인
	bool IsHpFull();
	//Idle 연속 확인
	bool IsConsecutiveIdle;

	void PlayerHudInit();
#pragma endregion HUDPrivate
public:
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();
	void Begin();

#pragma region HUDPublic
	// 
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
	//현재 스테미나 비율 전환
	float GetStaminaRatio();

	//사운드 출력
	void FootStepSound();
	
	//Hp RecoveryBar 
	float GetHpRecoveryRatio();

	void UpdateFireCool(float CurCool,float MaxCool);
	void UpdateWaterCool(float CurCool, float MaxCool);
	void UpdateThunderCool(float CurCool, float MaxCool);

	//Fire Cool
	float GetFireCoolRatio();
	//Water Cool
	float GetWaterCoolRatio();
	//Thunde Cool
	float GetThunderCoolRatio();

	float GetFireSkillCoolRatio();
	float GetWaterSkillCoolRatio();
	float GetThunderSkillCoolRatio();

	int  GetSkillCount();
	void  SetSkillCount(int Value);
	void PlayHUDAnimation();

	void UpdateFireSkillCool(float CurCool, float MaxCool);
	void UpdateWaterSkillCool(float CurCool, float MaxCool);
	void UpdateThunderSkillCool(float CurCool, float MaxCool);

	void SetDialogState(const bool State);
#pragma endregion HUDPublic


#pragma region PauseWidgetFunc
public:
	void PauseWidgetOn();
	void PauseWidgetOff();
	bool GetIsPauseOnScreen();
#pragma endregion PauseWidgetFunc
};
