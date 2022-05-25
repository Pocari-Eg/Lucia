// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

#include "DialogWidget.h"
#include "RaidMonsterWidget.h"
#include "../EnemySource/Monster.h"

#include "PlayerHudWidget.generated.h"

/**
 * 
 */


USTRUCT()
struct FSkillImageData
{
	GENERATED_BODY()
		//속성 관련 데이터
	UPROPERTY()
	class UImage* SelectIcon;
	UPROPERTY()
	class UImage* NoneSelectIcon;
	UPROPERTY()
	class UProgressBar* CoolTimeBar;
	UPROPERTY()
	class UImage* Active;

};
UCLASS()
class STARRYTAIL_API UPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Player 바인드 할떄 사용 
	void BindCharacter(class AIreneCharacter* NewIrene);

	void SetDialog(FString dialog);
	void PlayDialog();
	void RaidWidgetbind(AMonster* RadiMonster);

	void ActionWidgetOn();
	void ActionWidgetOff();
private:

	void UpdateHp();
	void UpdateMp();
	void UpdateHpRecovery();

	void UpdateAttributes();

	void InitSkillUI();

	void UpdateCooTime();

	void FireSelect();
	void WaterSelect();
	void ThunderSelect();

protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
private:

	//현재 오브젝트
	class AIreneCharacter* CurrentIrene;
	//위젯 안 HP Bar 데이터
	UPROPERTY()
	class UProgressBar* HPProgressBar;
	UPROPERTY()
	class UProgressBar* HPRecoveryProgressBar;
	UPROPERTY()
	class UProgressBar* MPProgressBar;	

	UPROPERTY()
	class UDialogWidget* DialogWidget;
	UPROPERTY()
	class URaidMonsterWidget* RMWidget;
	UPROPERTY()
	class UUserWidget* ActionWidget;

	FSkillImageData Fire;
	FSkillImageData Water;
	FSkillImageData Thunder;


	FString DialogText;

};
