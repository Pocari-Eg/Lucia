// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

#include "DialogWidget.h"
#include "RaidMonsterWidget.h"
#include "../EnemySource/Monster.h"
#include "ScriptDataTable.h"
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

	void RaidWidgetbind(AMonster* RadiMonster);

	void ActionWidgetOn();
	void ActionWidgetOff();

	UFUNCTION(BlueprintImplementableEvent)
	void  OnFireAttribute();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnWaterAttribute();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnThunderAttribute();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHUDAnimation();


	//���̾�α�
	

	EDialogState GetDialogState();
	void SetDialogState(EDialogState NewState);

	void SetDialog(TArray<FScriptData*> Data);
	void PlayDialog();
	void SkipDialog();
	void ExitDialog();


	void PlayPopUp(TArray<FScriptData*> Data);
	
	bool ContinueDialog();
private:

	void UpdateHp();
	void UpdateMp();
	void UpdateHpRecovery();

	void UpdateAttributes();

	void InitSkillUI();

	void UpdateFireCoolTime();
	void UpdateWaterCoolTime();
	void UpdateThunderCoolTime();

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
	class UDialogWidget* PopUpWidget;
	UPROPERTY()
	class URaidMonsterWidget* RMWidget;
	UPROPERTY()
	class UUserWidget* ActionWidget;

	FSkillImageData Fire;
	FSkillImageData Water;
	FSkillImageData Thunder;

	bool isFirst;


	TArray<FScriptData*> ScriptData;

	int32 DialogNum;
};
