// Fill out your copyright notice in the Description page of Project Settings.


#include "StanceGaugeWidget_D.h"
#include "Components/Image.h"

void UStanceGaugeWidget_D::ResetStanceGague()
{
	PLUS = 0.0f;
	mat_Progress->SetScalarParameterValue("Progress", 0.0f);
}

void UStanceGaugeWidget_D::eCtime(float Ctime)
{
	PLUS += Ctime;
	auto MAT = gauge_full->GetDynamicMaterial();
	MAT->SetScalarParameterValue("Progress", PLUS / 100.0f);
}

void UStanceGaugeWidget_D::eCtimeflow()
{
	
}
