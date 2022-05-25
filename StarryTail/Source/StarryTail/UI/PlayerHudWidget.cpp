// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/IreneUIManager.h"
#include"../PlayerSource/IreneAttackInstance.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//���ε��� object�� CurrentObject�� �Ҵ�
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//��������Ʈ�� ���� UpdateWidget�Լ��� ȣ��ɼ� �ֵ��� 

	NewIrene->IreneUIManager->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	NewIrene->IreneUIManager->OnStaminaChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
	NewIrene->FOnAttributeChange.AddUObject(this, &UPlayerHudWidget::UpdateAttributes);
}

void UPlayerHudWidget::SetDialog(FString dialog)
{
	DialogText=dialog;
}

void UPlayerHudWidget::PlayDialog()
{
	DialogWidget->SetDialog(*DialogText);
}

void UPlayerHudWidget::RaidWidgetbind(AMonster* RadiMonster)
{
	RMWidget->BindMonster(RadiMonster);
}

void UPlayerHudWidget::UpdateHp()
{
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
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
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
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

void UPlayerHudWidget::UpdateCooTime()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Fire.CoolTimeBar)
		{
			//Fire.CoolTimeBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRatio());
		}
		if (nullptr != Water.CoolTimeBar)
		{
			//Water.CoolTimeBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRatio());
		}
		if (nullptr != Thunder.CoolTimeBar)
		{
			//Thunder.CoolTimeBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRatio());
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
	RMWidget->SetVisibility(ESlateVisibility::Hidden);


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
	ActionWidgetOff();

}
