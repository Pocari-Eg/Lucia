// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../../UI/PlayerHudWidget.h"
#include"../../UI/PauseWidget.h"

#include "IreneUIManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChangeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSoulUpdateDelegate);

UCLASS()
class STARRYTAIL_API UIreneUIManager : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY()
	AIreneCharacter* Irene;

	//현재 회복 대기 시간
	float CurRecoverWaitTime;
	//현재 회복 시간
	float CurRecoverTime;
	//남은 회복량
	float RemainingRecovery;
	//타이머 핸들
	FTimerHandle HpRecoveryTimerHandle;
	FTimerHandle HpRecoveryWaitTimerHandle;

	float MaxSoulValue;
	float CurSoulValue;

#pragma region HUD
public:
	FOnHpChangeDelegate OnHpChanged;
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UPlayerHudWidget> PlayerHudClass;   // 위젯 클래스 

	FOnSoulUpdateDelegate OnSoulUpdate;
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
	void Begin();

private:
	void SetIreneCharacter(AIreneCharacter* Value);
	void InitMemberVariable();

#pragma region HUDPublic
public:
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

	
	//Hp RecoveryBar 
	float GetHpRecoveryRatio();

	void UpdateSoul(float CurSoul, float MaxSoul);


	//Thunde Cool
	float GetSoulRatio();
	void PlayHUDAnimation();
	
	void SetDialogState(const bool State);

	void HpRecovery(float Hp);


	void HpFullRecovery();
#pragma endregion HUDPublic


#pragma region PauseWidgetFunc
public:
	void PauseWidgetOn();
	void PauseWidgetOff();
	bool GetIsPauseOnScreen();
#pragma endregion PauseWidgetFunc
};
