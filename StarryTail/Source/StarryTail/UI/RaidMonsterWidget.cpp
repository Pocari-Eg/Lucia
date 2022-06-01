// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidMonsterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
void URaidMonsterWidget::BindScientia(class AScientia* NewScientia) {

	CurrentScientia = NewScientia;

	UpdateAttribute();

	CurrentScientia->AttributeChange.AddUObject(this, &URaidMonsterWidget::UpdateAttribute);
	CurrentScientia->OnHpChanged.AddUObject(this, &URaidMonsterWidget::UpdateHp);
	
	CurrentScientia->OnFireBarrierChanged.AddUObject(this, &URaidMonsterWidget::UpdateFireDef);
	CurrentScientia->OnWaterBarrierChanged.AddUObject(this, &URaidMonsterWidget::UpdateWaterDef);
	CurrentScientia->OnThunderBarrierChanged.AddUObject(this, &URaidMonsterWidget::UpdateThunderDef);

	CurrentScientia->OnCrushBarrier.AddUObject(this, &URaidMonsterWidget::BreakAttributeBarrier);
	SetVisibility(ESlateVisibility::Visible);

	STARRYLOG_S(Warning);
}

void URaidMonsterWidget::UpdateHp()
{

	if (CurrentScientia != nullptr)		
	{
	
		if (HPProgressBar != nullptr)
		{
			
			HPProgressBar->SetPercent(CurrentScientia->GetHpRatio());
		}
	}
	
}

void URaidMonsterWidget::UpdateFireDef()
{
	if (CurrentScientia != nullptr)
	{
		if (FireDefBar != nullptr)
		{

			FireDefBar->SetPercent(CurrentScientia->GetFireDefPercent());
		}
	}
}

void URaidMonsterWidget::UpdateWaterDef()
{
	if (CurrentScientia != nullptr)
	{
		if (WaterDefBar != nullptr)
		{
			WaterDefBar->SetPercent(CurrentScientia->GetWaterDefPercent());
		}
	}

}

void URaidMonsterWidget::UpdateThunderDef()
{
	if (CurrentScientia != nullptr)
	{
		if (ThunderDefBar != nullptr)
		{
			ThunderDefBar->SetPercent(CurrentScientia->GetThunderDefPercent());
		}
	}

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
			break;
		case EAttributeKeyword::e_Water:
	
			FireDefBar->SetVisibility(ESlateVisibility::Hidden);
			WaterDefBar->SetVisibility(ESlateVisibility::Visible);
			ThunderDefBar->SetVisibility(ESlateVisibility::Hidden);
			break;
		case EAttributeKeyword::e_Thunder:

			FireDefBar->SetVisibility(ESlateVisibility::Hidden);
			WaterDefBar->SetVisibility(ESlateVisibility::Hidden);
			ThunderDefBar->SetVisibility(ESlateVisibility::Visible);
			break;
		}
	}
	
}

void URaidMonsterWidget::BreakAttributeBarrier()
{
	
		switch (CurrentScientia->GetScInfo().CurrentAttribute)
		{
		case EAttributeKeyword::e_Fire:
			Fire.Standard->SetVisibility(ESlateVisibility::Hidden);
			Fire.Break->SetVisibility(ESlateVisibility::Visible);
			break;
		case EAttributeKeyword::e_Water:

			Water.Standard->SetVisibility(ESlateVisibility::Hidden);
			Water.Break->SetVisibility(ESlateVisibility::Visible);
			break;
		case EAttributeKeyword::e_Thunder:

			Thunder.Standard->SetVisibility(ESlateVisibility::Hidden);
			Thunder.Break->SetVisibility(ESlateVisibility::Visible);
			break;
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

	 Fire.Standard= Cast<UImage>(GetWidgetFromName(TEXT("Fire")));
	 Fire.Break = Cast<UImage>(GetWidgetFromName(TEXT("FireBreak")));
	 Water.Standard = Cast<UImage>(GetWidgetFromName(TEXT("Water")));
	 Water.Break = Cast<UImage>(GetWidgetFromName(TEXT("WaterBreak")));
	 Thunder.Standard = Cast<UImage>(GetWidgetFromName(TEXT("Thunder")));
	 Thunder.Break = Cast<UImage>(GetWidgetFromName(TEXT("ThunderBreak")));
}

