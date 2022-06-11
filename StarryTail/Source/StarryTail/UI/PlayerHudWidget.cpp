// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/IreneUIManager.h"
#include"../PlayerSource/IreneAttackInstance.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//새로들어온 object를 CurrentObject에 할당
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 

	NewIrene->IreneUIManager->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	NewIrene->IreneUIManager->OnStaminaChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
	NewIrene->FOnAttributeChange.AddUObject(this, &UPlayerHudWidget::UpdateAttributes);

	NewIrene->IreneUIManager->OnFireCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateFireCoolTime);
	NewIrene->IreneUIManager->OnWaterCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateWaterCoolTime);
	NewIrene->IreneUIManager->OnThunderCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateThunderCoolTime);

	NewIrene->IreneUIManager->OnFireSkillCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateFireSkillCoolTime);
	NewIrene->IreneUIManager->OnWaterSkillCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateWaterSkillCoolTime);
	NewIrene->IreneUIManager->OnThunderSkillCoolChange.AddUObject(this, &UPlayerHudWidget::UpdateThunderSkillCoolTime);
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

void UPlayerHudWidget::UseSkill()
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

EAttributeKeyword UPlayerHudWidget::GetAttriburte()
{
	return CurrentIrene->GetAttribute();
}

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

void UPlayerHudWidget::UpdateMp()
{
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentIrene != nullptr)
	{
		if (nullptr != MPProgressBar)
		{
			float ratio = CurrentIrene->IreneUIManager->GetStaminaRatio();
			MPProgressBar->SetPercent(ratio);
			if (ratio < SPLimit)
			{
				MPProgressBar->SetFillColorAndOpacity(FLinearColor(1.0f,0.0f,0.0f,1.0f));
			}
			else {
				MPProgressBar->SetFillColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
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


void UPlayerHudWidget::UpdateAttributes()
{
	switch (CurrentIrene->IreneAttack->GetAttribute())
	{
	case EAttributeKeyword::e_Fire:
		FireSelect();
		break;
	case EAttributeKeyword::e_Water:
		WaterSelect();
		break;
	case EAttributeKeyword::e_Thunder:
		ThunderSelect();
		break;
	}


	if (isFirst)
	{
		InitAttributeUI();
		isFirst = false;
	}
}

void UPlayerHudWidget::InitAttributeUI()
{
	//Fire
	Fire.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Fire.NoneSelectIcon->SetVisibility(ESlateVisibility::Visible);
	Fire.Active->SetVisibility(ESlateVisibility::Hidden);
	

	//Water
	Water.SelectIcon->SetVisibility(ESlateVisibility::Visible);
	Water.NoneSelectIcon->SetVisibility(ESlateVisibility::Visible);
	Water.Active->SetVisibility(ESlateVisibility::Visible);


	//Thunder
	Thunder.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Thunder.NoneSelectIcon->SetVisibility(ESlateVisibility::Visible);
	Thunder.Active->SetVisibility(ESlateVisibility::Hidden);


}

void UPlayerHudWidget::UpdateFireCoolTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Fire.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetFireCoolRatio();
			Fire.CoolTimeBar->SetPercent(Ratio);
			if (Ratio >= 1.0f)
			{
				Fire.NoneSelectIcon->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UPlayerHudWidget::UpdateWaterCoolTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Water.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetWaterCoolRatio();
			Water.CoolTimeBar->SetPercent(Ratio);
			if (Ratio >= 1.0f)
			{
				Water.NoneSelectIcon->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void UPlayerHudWidget::UpdateThunderCoolTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Thunder.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetThunderCoolRatio();
			Thunder.CoolTimeBar->SetPercent(Ratio);
			if (Ratio >= 1.0f)
			{
				Thunder.NoneSelectIcon->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}



void UPlayerHudWidget::UpdateFireSkillCoolTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != FireSkill.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetFireSkillCoolRatio();
			FireSkill.CoolTimeBar->SetPercent(Ratio);

			if (Ratio >= 1.0f)
			{
			
				STARRYLOG_S(Error);
				FireSkill.Active->SetVisibility(ESlateVisibility::Visible);

			}
		}

	
	}
}

void UPlayerHudWidget::UpdateWaterSkillCoolTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != WaterSkill.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetWaterSkillCoolRatio();
			WaterSkill.CoolTimeBar->SetPercent(Ratio);

			if (Ratio >= 1.0f)
			{
		    	WaterSkill.Active->SetVisibility(ESlateVisibility::Visible);
			}
		}


	}
}

void UPlayerHudWidget::UpdateThunderSkillCoolTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != ThunderSkill.CoolTimeBar)
		{
			float Ratio = CurrentIrene->IreneUIManager->GetThunderSkillCoolRatio();
			ThunderSkill.CoolTimeBar->SetPercent(Ratio);

			if (Ratio >= 1.0f)
			{
			
				int Count = CurrentIrene->IreneUIManager->GetSkillCount() + 1;
				CurrentIrene->IreneUIManager->SetSkillCount(Count);
				ThunderSkillActive[Count - 1]->SetVisibility(ESlateVisibility::Visible);
				if (Count == 2)
				{
						ThunderSkill.Active->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}


	}
}

void UPlayerHudWidget::FireSelect()
{
	//Fire
	Fire.SelectIcon->SetVisibility(ESlateVisibility::Visible);
	Fire.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Fire.Active->SetVisibility(ESlateVisibility::Visible);


	//Water
	Water.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Water.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Water.Active->SetVisibility(ESlateVisibility::Hidden);


	//Thunder
	Thunder.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Thunder.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Thunder.Active->SetVisibility(ESlateVisibility::Hidden);

	
	SPLimit = 0.25f;

	//Skill
	OnFireAttribute();
}

void UPlayerHudWidget::WaterSelect()
{
	//Fire
	Fire.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Fire.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Fire.Active->SetVisibility(ESlateVisibility::Hidden);


	//Water
	Water.SelectIcon->SetVisibility(ESlateVisibility::Visible);
	Water.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Water.Active->SetVisibility(ESlateVisibility::Visible);


	//Thunder
	Thunder.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Thunder.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Thunder.Active->SetVisibility(ESlateVisibility::Hidden);

	SPLimit = 0.5f;

	//Skill
	OnWaterAttribute();
}

void UPlayerHudWidget::ThunderSelect()
{
	//Fire
	Fire.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Fire.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Fire.Active->SetVisibility(ESlateVisibility::Hidden);


	//Water
	Water.SelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Water.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Water.Active->SetVisibility(ESlateVisibility::Hidden);


	//Thunder
	Thunder.SelectIcon->SetVisibility(ESlateVisibility::Visible);
	Thunder.NoneSelectIcon->SetVisibility(ESlateVisibility::Hidden);
	Thunder.Active->SetVisibility(ESlateVisibility::Visible);

	SPLimit = 0.25f;

	//Skill
	OnThunderAttribute();
}




void UPlayerHudWidget::ActionWidgetOn()
{
	ActionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHudWidget::ActionWidgetOff()
{
	ActionWidget->SetVisibility(ESlateVisibility::Hidden);
}



void UPlayerHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("Init"));
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
	HPRecoveryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_RecoverBar")));

	DialogWidget = Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_DialogWidget")));
	RMWidget = Cast<URaidMonsterWidget>(GetWidgetFromName(TEXT("BP_RaidMonsterWidget")));
	ActionWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("BP_ActionWidget")));
	PopUpWidget= Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_PopUpWidget")));
	TutorialWidget = Cast<UTutorialWidget>(GetWidgetFromName(TEXT("BP_TutorialWidget")));

	Fire.SelectIcon=Cast<UImage>(GetWidgetFromName(TEXT("Fire_Select")));
	Fire.NoneSelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("Fire_NoneSelect")));
	Fire.Active = Cast<UImage>(GetWidgetFromName(TEXT("Fire_Active")));
	Fire.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Fire_CoolTime")));


	Water.SelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("Water_Select")));
	Water.NoneSelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("Water_NoneSelect")));
	Water.Active = Cast<UImage>(GetWidgetFromName(TEXT("Water_Active")));
	Water.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Water_CoolTime")));

	Thunder.SelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("Thunder_Select")));
	Thunder.NoneSelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("Thunder_NoneSelect")));
	Thunder.Active = Cast<UImage>(GetWidgetFromName(TEXT("Thunder_Active")));
	Thunder.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("Thunder_CoolTime")));

	FireSkill.NoneSelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("FireSkillOff")));
	FireSkill.Active = Cast<UImage>(GetWidgetFromName(TEXT("FireSkillOn")));
	FireSkill.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("FireSkill_CoolTime")));

	WaterSkill.NoneSelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("WaterSkillOff")));
	WaterSkill.Active = Cast<UImage>(GetWidgetFromName(TEXT("WaterSkillOn")));
	WaterSkill.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("WaterSkill_CoolTime")));

	ThunderSkill.NoneSelectIcon = Cast<UImage>(GetWidgetFromName(TEXT("ThunderSkillOff")));
	ThunderSkill.Active = Cast<UImage>(GetWidgetFromName(TEXT("ThunderSkillOn")));
	ThunderSkill.CoolTimeBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ThunderSkill_CoolTime")));
	
	ThunderSKillCount.SetNum(2);
	ThunderSkillActive.SetNum(2);

	ThunderSKillCount[0] = Cast<UImage>(GetWidgetFromName(TEXT("Skill_1")));
	ThunderSKillCount[1] = Cast<UImage>(GetWidgetFromName(TEXT("Skill_2")));

	ThunderSkillActive[0] = Cast<UImage>(GetWidgetFromName(TEXT("Skill_1_Acitve")));
	ThunderSkillActive[1] = Cast<UImage>(GetWidgetFromName(TEXT("Skill_2_Acitve")));


	InitAttributeUI();

	isFirst = true;
	ActionWidgetOff();

}
