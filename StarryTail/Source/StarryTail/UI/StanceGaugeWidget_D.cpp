// Fill out your copyright notice in the Description page of Project Settings.


#include "StanceGaugeWidget_D.h"
#include "Components/Image.h"

void UStanceGaugeWidget_D::eCtime(float Ctime)
{
	Ctime_n = Ctime;
	Ctime_f = Ctime;
	GetWorld()->GetTimerManager().ClearTimer(AttackCtimeHandle);

	mat_Progress = gauge_full->GetDynamicMaterial();
	mat_Progress->SetScalarParameterValue("Progress", 1.0f);

	GetWorld()->GetTimerManager().SetTimer(AttackCtimeHandle, this, &UStanceGaugeWidget_D::eCtimeflow, 0.05f, true, 0.05f);

}

void UStanceGaugeWidget_D::eCtimeflow()
{
	if (Ctime_f <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackCtimeHandle);
		mat_Progress->SetScalarParameterValue("Progress", 0.0f);
		return;
	}

	Ctime_f -= 0.05f;
	mat_Progress->SetScalarParameterValue("Progress", Ctime_f / Ctime_n);
}
