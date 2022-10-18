// Fill out your copyright notice in the Description page of Project Settings.


#include "UltimateGaugeWidget_D.h"
#include "Components/ProgressBar.h"


void UUltimateGaugeWidget_D::SetUltimate(float pErcent)
{
	auto _pErcent = ultimate_fillBar->Percent + (pErcent / 100.0f);
	ultimate_fillBar->SetPercent(_pErcent);
}