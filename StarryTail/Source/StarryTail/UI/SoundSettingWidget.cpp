// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundSettingWidget.h"

void USoundSettingWidget::WidgetOn(UPauseWidget* widget)
{
	PauseWidget = widget;
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	this->SetVisibility(ESlateVisibility::Visible);
}

void USoundSettingWidget::WidgetOff()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
}
