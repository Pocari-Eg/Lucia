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

}

void UPlayerHudWidget::SetDialog(TArray<FScriptData*> Data)
{

	DialogNum = 0;
	SetDialogState(EDialogState::e_Set);
	ScriptData= Data;
}

void UPlayerHudWidget::PlayDialog()
{
	SetDialogState(EDialogState::e_Playing);
	DialogWidget->SetDialog(ScriptData[DialogNum]);
}

void UPlayerHudWidget::SkipDialog()
{
	DialogWidget->SkipDialog();
}

void UPlayerHudWidget::PlayPopUp(TArray<FScriptData*> Data)
{
	DialogNum = 0;
	SetDialogState(EDialogState::e_Set);
	ScriptData = Data;
	SetDialogState(EDialogState::e_Playing);
	PopUpWidget->SetDialog(ScriptData[DialogNum]);
}

void UPlayerHudWidget::ExitDialog()
{
	if (ActionWidget->Visibility == ESlateVisibility::Hidden) {
		SetDialogState(EDialogState::e_Disable);
	}
	else if (ActionWidget->Visibility == ESlateVisibility::Visible)
	{
		SetDialogState(EDialogState::e_Set);
	}
	DialogNum = 0;
	DialogWidget->EndDialog();
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

EDialogState UPlayerHudWidget::GetDialogState()
{
	return DialogWidget->GetDialogState();
}

void UPlayerHudWidget::SetDialogState(EDialogState NewState)
{
	DialogWidget->SetDialogState(NewState);
}

void UPlayerHudWidget::RaidWidgetbind(AMonster* RadiMonster)
{
	RMWidget->BindMonster(RadiMonster);
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
			MPProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetStaminaRatio());
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
		InitSkillUI();
		isFirst = false;
	}
}

void UPlayerHudWidget::InitSkillUI()
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
	RMWidget->SetVisibility(ESlateVisibility::Visible);
	PopUpWidget= Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_PopUpWidget")));

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

	InitSkillUI();

	isFirst = true;
	ActionWidgetOff();

}
