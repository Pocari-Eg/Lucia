// Fill out your copyright notice in the Description page of Project Settings.


#include "StanceGaugeWidget_D.h"
#include "Components/Image.h"
#include "../PlayerSource/IreneCharacter.h"

void UStanceGaugeWidget_D::ResetStanceGague()
{
	/*GetWorld()->GetTimerManager().ClearTimer(AttackCtimeHandle);

	PLUS = 0.0f;
	auto MAT = gauge_full->GetDynamicMaterial();
	MAT->SetScalarParameterValue("Progress", 0.0f);*/
}

void UStanceGaugeWidget_D::eCtime(float Ctime)
{
	/*if (Ctime == -1.0f)
	{
		ResetStanceGague();
		return;
	}
	else if (Ctime == -2.0f)
	{
		SetCoolTime(60.0f);
		return;
	}
	PLUS += Ctime;
	auto MAT = gauge_full->GetDynamicMaterial();
	MAT->SetScalarParameterValue("Progress", PLUS / 100.0f);*/
}

void UStanceGaugeWidget_D::SetCoolTime(float Time)
{
	/*Timer = Time;
	maxTimer = Time;
	GetWorld()->GetTimerManager().SetTimer(AttackCtimeHandle, this, &UStanceGaugeWidget_D::eCtimeflow, 0.05f, true, 0.05f);*/
}

void UStanceGaugeWidget_D::eCtimeflow()
{
	/*Timer -= 0.05f;
	if (Timer <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackCtimeHandle);
		return;
	}

	auto MAT = gauge_full->GetDynamicMaterial();
	MAT->SetScalarParameterValue("Progress", Timer / maxTimer);*/
}

void UStanceGaugeWidget_D::NativeConstruct()
{
	Super::NativeConstruct();

	Irene = Cast<AIreneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UStanceGaugeWidget_D::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Irene == nullptr) return;

	auto MAT = gauge_full->GetDynamicMaterial();
	MAT->SetScalarParameterValue("Progress", Irene->IreneData.CurrentGauge / 100.0f);
}
