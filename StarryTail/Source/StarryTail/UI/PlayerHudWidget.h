// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Engine/Canvas.h"

#include "DialogWidget.h"
#include "RaidMonsterWidget.h"
#include "TutorialWidget.h"
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

	void Scientiabind(AScientia* CurrentScientia);

	void ActionWidgetOn();
	void ActionWidgetOff();


	//Event
	UFUNCTION(BlueprintImplementableEvent)
	void  OnFireAttribute();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnWaterAttribute();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnThunderAttribute();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayHUDAnimation();


	UFUNCTION(BlueprintImplementableEvent)
	void PlayerHudOn();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerHudOff();


	UFUNCTION(BlueprintImplementableEvent)
	void StageNamePlayEvent();

	void StageNamePlay(FText Text);
	//���̾�α�
	
	EDialogState GetDialogState();
	void SetDialogState(EDialogState NewState);

	void SetDialog(TArray<FScriptData*> Data);
	void PlayDialog();
	void PassDialog();
	void ExitDialog();


	void SetPopUp(TArray<FScriptData*> Data);
	void PlayPopUp();
	void ExitPopUp();
	bool ContinueDialog();
	void SkipDialog();


//	void UseSkill();
	UFUNCTION(BluePrintCallable)
	EAttributeKeyword GetAttriburte();

	UFUNCTION(BluePrintCallable)
	void SetTutorial(FString Num);
private:

	void UpdateHp();
	void UpdateHpRecovery();

	void UpdateSwordAttributes();
	void UpdateQuillAttributes();

	void UpdateFireCoolTime();
	void UpdateWaterCoolTime();
	void UpdateThunderCoolTime();

	/*void UpdateFireSkillCoolTime();
	void UpdateWaterSkillCoolTime();
	void UpdateThunderSkillCoolTime();*/
	
	void InitAttributeUI();

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
	class UTutorialWidget* TutorialWidget;
	UPROPERTY()
	class UUserWidget* ActionWidget;

	FSkillImageData Fire;
	//FSkillImageData FireSkill;

	FSkillImageData Water;
	//FSkillImageData WaterSkill;

	FSkillImageData Thunder;
	//FSkillImageData ThunderSkill;
	
	//TArray<UImage*> ThunderSKillCount;
	//TArray<UImage*> ThunderSkillActive;

	bool isFirst;

	TArray<FScriptData*> ScriptData;

	int32 DialogNum;

	float SPLimit;

public:
		UPROPERTY(BluePrintReadOnly)
		FText StageTitle;

		UPROPERTY(BluePrintReadOnly)
		bool bIsFirstLevel;
};
