// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateGaugeWidget_D.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UUltimateGaugeWidget_D::SetUltimate(float pErcent)
{
	
}

void UUltimateGaugeWidget_D::SetUltimateBlueprint(float pErcent)
{
	ultimate_fillBar->SetPercent(pErcent / 100.0f);

	SetColors(pErcent);
}

void UUltimateGaugeWidget_D::SetColors(float _current)
{
	if (_current > 0.0f && _current < 100.0f)
	{
		if (ultimate_fillBar->WidgetStyle.FillImage.TintColor == Fill) return;

		ultimate_fillBar->SetFillColorAndOpacity(Fill);
	}
	else if (_current >= 100.0f)
	{
		if (ultimate_fillBar->WidgetStyle.FillImage.TintColor == full) return;

		ultimate_fillBar->SetFillColorAndOpacity(full);
	}
}
