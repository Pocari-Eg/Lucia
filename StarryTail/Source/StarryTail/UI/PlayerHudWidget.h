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
		//�Ӽ� ���� ������
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
	// Player ���ε� �ҋ� ��� 
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
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
private:

	//���� ������Ʈ
	class AIreneCharacter* CurrentIrene;
	//���� �� HP Bar ������
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
