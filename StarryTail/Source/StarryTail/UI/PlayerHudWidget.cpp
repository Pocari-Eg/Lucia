// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/PlayerInstance/IreneUIManager.h"
#include"../PlayerSource/PlayerInstance/IreneAttackInstance.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//새로들어온 object를 CurrentObject에 할당
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 

	NewIrene->IreneUIManager->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);

	NewIrene->IreneUIManager->OnSoulUpdate.AddUObject(this, &UPlayerHudWidget::UpdateSoulGauge);

	/*NewIrene->IreneUIManager->OnFireSkillCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateFireSkillCoolTime);
	NewIrene->IreneUIManager->OnWaterSkillCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateWaterSkillCoolTime);
	NewIrene->IreneUIManager->OnThunderSkillCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateThunderSkillCoolTime);*/
}

void UPlayerHudWidget::SetDialog(TArray<FScriptData*> Data)
{
	DialogNum = 0;
	SetDialogState(EDialogState::e_Set);
	ScriptData= Data;
}

void UPlayerHudWidget::PlayDialog()
{
	if (ScriptData[DialogNum]->Type == 0) {
		SetDialogState(EDialogState::e_Playing);
		DialogWidget->SetDialog(ScriptData[DialogNum]);
		PlayerHudOff();
		CurrentIrene->IreneUIManager->SetDialogState(true);
	}
	else {
		PlayPopUp();
	}
}

void UPlayerHudWidget::PassDialog()
{
	if (ScriptData[DialogNum]->Type == 0) {
		DialogWidget->PassDialog();
	}

}

void UPlayerHudWidget::SetPopUp(TArray<FScriptData*> Data)
{
	DialogNum = 0;
	SetDialogState(EDialogState::e_Set);
	ScriptData = Data;
	PopUpWidget->BindPlayerHud(this);

	if (ScriptData[0]->Condition == 0)
	{
		PlayPopUp();
	}
	
}

void UPlayerHudWidget::PlayPopUp()
{
	PopUpWidget->DialogTimerClear();
	SetDialogState(EDialogState::e_Playing);
	PopUpWidget->SetDialog(ScriptData[DialogNum]);
}

void UPlayerHudWidget::ExitPopUp()
{
	PopUpWidget->DialogTimerClear();
	SetDialogState(EDialogState::e_Disable);
	DialogNum = 0;

	ScriptData.Empty();
	ScriptData.SetNum(0);

	PopUpWidget->EndDialog();
}

void UPlayerHudWidget::ExitDialog()
{

	if (ScriptData[0]->Type == 0) {
		DialogNum = 0;
		DialogWidget->EndDialog();
		PlayerHudOn();
		CurrentIrene->IreneUIManager->SetDialogState(false);
	}
	if (ActionWidget->Visibility == ESlateVisibility::Hidden) {
		SetDialogState(EDialogState::e_Disable);
		ScriptData.Empty();
		ScriptData.SetNum(0);
	}
	else if (ActionWidget->Visibility == ESlateVisibility::Visible)
	{
		SetDialogState(EDialogState::e_Set);
	}
}

bool UPlayerHudWidget::ContinueDialog()
{
	DialogNum++;
	if (DialogNum < ScriptData.Num()) {
		return true;
	}
	else {
		return false;
	}
	
}

void UPlayerHudWidget::SkipDialog()
{
	DialogWidget->DialogTimerClear();
	
	ExitDialog();
	ScriptData.Empty();
	ScriptData.SetNum(0); 
}

/*void UPlayerHudWidget::UseSkill()
{

	STARRYLOG_S(Error);
	switch (CurrentIrene->GetAttribute())
	{
	case EAttributeKeyword::e_Fire:
		STARRYLOG_S(Error);
		FireSkill.Active->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EAttributeKeyword::e_Water:
		STARRYLOG_S(Error);
		WaterSkill.Active->SetVisibility(ESlateVisibility::Hidden);
		break;
	case EAttributeKeyword::e_Thunder:
		STARRYLOG_S(Error);
		ThunderSkill.Active->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:
		break;
	}

	if (CurrentIrene->GetAttribute() == EAttributeKeyword::e_Thunder)
	{
		int Count = CurrentIrene->IreneUIManager->GetSkillCount() - 1;
		CurrentIrene->IreneUIManager->SetSkillCount(Count);
		ThunderSkillActive[Count]->SetVisibility(ESlateVisibility::Hidden);
	}
}
*/

void UPlayerHudWidget::SetTutorial(FString Num)
{
	TutorialWidget->PlayTutorial(Num);
}


void UPlayerHudWidget::StageNamePlay(FText Text)
{
	StageTitle = Text;
StageNamePlayEvent();
}

EDialogState UPlayerHudWidget::GetDialogState()
{
	return DialogWidget->GetDialogState();
}

void UPlayerHudWidget::SetDialogState(EDialogState NewState)
{
	DialogWidget->SetDialogState(NewState);
}

void UPlayerHudWidget::Scientiabind(AScientia* CurrentScientia)
{
	CurrentIrene->RaidBattleEvent();
	RMWidget->BindScientia(CurrentScientia);
}

void UPlayerHudWidget::UpdateHp()
{
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentIrene != nullptr)
	{
	
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRatio());
		}
	}
	UpdateHpRecovery();
}

void UPlayerHudWidget::UpdateHpRecovery()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != HPRecoveryProgressBar)
		{
			HPRecoveryProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRecoveryRatio());
		}
	}
}


void UPlayerHudWidget::UpdateSoulGauge()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Spear.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetSoulRatio();
			Spear.CoolTimeBar->SetPercent(Ratio);
			if (Ratio >= 1.0f)
			{
				Spear.Active->SetVisibility(ESlateVisibility::Visible);
			}
			else {
				Spear.Active->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}





void UPlayerHudWidget::ActionWidgetOn()
{
	ActionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHudWidget::ActionWidgetOff()
{
	ActionWidget->SetVisibility(ESlateVisibility::Hidden);
}

//void UPlayerHudWidget::NativeConstruct()
//{
//	Super::NativeConstruct();
//
//	UE_LOG(LogTemp, Warning, TEXT("Init"));
//	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
//	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
//	HPRecoveryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_RecoverBar")));
//
//	DialogWidget = Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_DialogWidget")));
//	RMWidget = Cast<URaidMonsterWidget>(GetWidgetFromName(TEXT("BP_RaidMonsterWidget")));
//	ActionWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("BP_ActionWidget")));
//	PopUpWidget= Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_PopUpWidget")));
//	TutorialWidget = Cast<UTutorialWidget>(GetWidgetFromName(TEXT("BP_TutorialWidget")));
//
//	Spear.Off = Cast<UImage>(GetWidgetFromName(TEXT("SpearOff")));
//	Spear.Active = Cast<UImage>(GetWidgetFromName(TEXT("SpearOn")));
//	Spear.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SpearUpdate")));
//
//	isFirst = true;
//
//
//	SetDialogState(EDialogState::e_Disable);
//	ActionWidgetOff();
//}

void UPlayerHudWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("Init"));
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
	HPRecoveryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_RecoverBar")));

	DialogWidget = Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_DialogWidget")));
	RMWidget = Cast<URaidMonsterWidget>(GetWidgetFromName(TEXT("BP_RaidMonsterWidget")));
	ActionWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("BP_ActionWidget")));
	PopUpWidget = Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_PopUpWidget")));
	TutorialWidget = Cast<UTutorialWidget>(GetWidgetFromName(TEXT("BP_TutorialWidget")));

	Spear.Off = Cast<UImage>(GetWidgetFromName(TEXT("SpearOff")));
	Spear.Active = Cast<UImage>(GetWidgetFromName(TEXT("SpearOn")));
	Spear.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("SpearUpdate")));

	isFirst = true;


	SetDialogState(EDialogState::e_Disable);
	ActionWidgetOff();
}
