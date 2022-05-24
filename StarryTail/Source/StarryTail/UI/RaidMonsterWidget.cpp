// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidMonsterWidget.h"
#include "Components/ProgressBar.h"

void URaidMonsterWidget::BindMonster(class AMonster* NewMonster) {

	//���ε��� object�� CurrentObject�� �Ҵ�
	CurrentMonster = Cast<AMonster>(NewMonster);

	//��������Ʈ�� ���� UpdateWidget�Լ��� ȣ��ɼ� �ֵ��� 

	//NewIrene->IreneUIManager->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	//NewIrene->IreneUIManager->OnStaminaChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
	//NewIrene->FOnAttributeChange.AddUObject(this, &UPlayerHudWidget::UpdateAttributes);
}

void URaidMonsterWidget::UpdateHp()
{
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
	if (CurrentMonster != nullptr)
	{

		if (nullptr != HPProgressBar)
		{
			//radiot
			//HPProgressBar->SetPercent(CurrentMonster->GetHp);
		}
	}
}

void URaidMonsterWidget::UpdateFireDef()
{
	
	if (CurrentMonster != nullptr)
	{

		if (nullptr != FireDefBar)
		{
			//radiot
			//HPProgressBar->SetPercent(CurrentMonster->GetHp);
		}
	}
}

void URaidMonsterWidget::UpdateWaterDef()
{

	if (CurrentMonster != nullptr)
	{

		if (nullptr != WaterDefBar)
		{
			//radiot
			//HPProgressBar->SetPercent(CurrentMonster->GetHp);
		}
	}
}

void URaidMonsterWidget::UpdateThunderDef()
{
	
	if (CurrentMonster != nullptr)
	{

		if (nullptr != ThunderDefBar)
		{
			//radiot
			//HPProgressBar->SetPercent(CurrentMonster->GetHp);
		}
	}
}

void URaidMonsterWidget::ChangeDefWidget()
{
	
	if (CurrentMonster != nullptr)
	{
		switch (CurrentMonster->GetAttribute())
		{
		case EAttributeKeyword::e_Fire :
			if (CheckDefWidget()) {
				FireDefBar->SetVisibility(ESlateVisibility::Visible);
				WaterDefBar->SetVisibility(ESlateVisibility::Hidden);
				ThunderDefBar->SetVisibility(ESlateVisibility::Hidden);
			}
				break;
		case EAttributeKeyword::e_Water:
			if (CheckDefWidget()) {
				FireDefBar->SetVisibility(ESlateVisibility::Hidden);
				WaterDefBar->SetVisibility(ESlateVisibility::Visible);
				ThunderDefBar->SetVisibility(ESlateVisibility::Hidden);
			}
			break;
		case EAttributeKeyword::e_Thunder:
			if (CheckDefWidget()) {
				FireDefBar->SetVisibility(ESlateVisibility::Hidden);
				WaterDefBar->SetVisibility(ESlateVisibility::Hidden);
				ThunderDefBar->SetVisibility(ESlateVisibility::Visible);
			}
			break;
		default:
			break;
		}
	}
}

bool URaidMonsterWidget::CheckDefWidget()
{ 
	if (FireDefBar == nullptr)return false;
	if (WaterDefBar == nullptr)return false;
	if (ThunderDefBar == nullptr)return false;

	return true;
}

void URaidMonsterWidget::NativeOnInitialized()
{

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_HPBar")));
	FireDefBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_FireDefBar")));
	WaterDefBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_WaterDefBar")));
	ThunderDefBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_ThunderBar")));

}

