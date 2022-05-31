// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidMonsterWidget.h"
#include "Components/ProgressBar.h"

void URaidMonsterWidget::BindScientia(class AScientia* NewScientia) {

	CurrentScientia = NewScientia;

	UpdateAttribute();

	CurrentScientia->AttributeChange.AddUObject(this, &URaidMonsterWidget::UpdateAttribute);
}

void URaidMonsterWidget::UpdateHp()
{
	
}

void URaidMonsterWidget::UpdateFireDef()
{
	
}

void URaidMonsterWidget::UpdateWaterDef()
{


}

void URaidMonsterWidget::UpdateThunderDef()
{
	

}

void URaidMonsterWidget::UpdateAttribute()
{
	if (CheckDefWidget()) {
		switch (CurrentScientia->GetScInfo().CurrentAttribute)
		{
		case EAttributeKeyword::e_None:
			FireDefBar->SetVisibility(ESlateVisibility::Hidden);
			WaterDefBar->SetVisibility(ESlateVisibility::Hidden);
			ThunderDefBar->SetVisibility(ESlateVisibility::Hidden);
			break;
		case EAttributeKeyword::e_Fire:
			FireDefBar->SetVisibility(ESlateVisibility::Visible);
			WaterDefBar->SetVisibility(ESlateVisibility::Hidden);
			ThunderDefBar->SetVisibility(ESlateVisibility::Hidden);
		case EAttributeKeyword::e_Water:
			FireDefBar->SetVisibility(ESlateVisibility::Hidden);
			WaterDefBar->SetVisibility(ESlateVisibility::Visible);
			ThunderDefBar->SetVisibility(ESlateVisibility::Hidden);
		case EAttributeKeyword::e_Thunder:
			FireDefBar->SetVisibility(ESlateVisibility::Hidden);
			WaterDefBar->SetVisibility(ESlateVisibility::Hidden);
			ThunderDefBar->SetVisibility(ESlateVisibility::Visible);
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
	 FireDefBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_FireDef")));
	 WaterDefBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_WaterDef")));
	 ThunderDefBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_ThunderDef")));

}

