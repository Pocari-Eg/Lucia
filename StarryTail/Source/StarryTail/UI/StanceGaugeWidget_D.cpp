// Fill out your copyright notice in the Description page of Project Settings.


#include "StanceGaugeWidget_D.h"
#include "Components/Image.h"
#include "../PlayerSource/IreneCharacter.h"
#include "Kismet/KismetMathLibrary.h"

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

void UStanceGaugeWidget_D::BrushSetColor(float _current)
{
	auto MAT = gauge_full->GetDynamicMaterial();
	if (_current <= 0.0f)
	{
		if (gauge_fill->Brush.TintColor == FSlateColor(idlecolor)) return;
		gauge_fill->SetBrushTintColor(FSlateColor(idlecolor));
	}
	else if (_current < 100.0f)
	{
		FLinearColor c;
		MAT->GetVectorParameterValue(FHashedMaterialParameterInfo(), c);

		if (c == fillcolor) return;
		MAT->SetVectorParameterValue("ProgressColor1", fillcolor);
		gauge_fill->SetBrushTintColor(FSlateColor(FLinearColor::White));
	}
	else if (_current >= 100.0f)
	{
		FLinearColor c;
		MAT->GetVectorParameterValue(FHashedMaterialParameterInfo(), c);

		if (c == fullcolor) return;
		MAT->SetVectorParameterValue("ProgressColor1", fullcolor);
		//SetShine();
		//GetWorld()->GetTimerManager().SetTimer(stopshine, this, &UStanceGaugeWidget_D::SetShine, 2.0f, false, 2.0f);
	}
}

void UStanceGaugeWidget_D::SetShine()
{
	SHINE = !SHINE;
	if (SHINE)
	{
		targetR = 1.0f;
		targetG = 0.838524f;
		targetB = 0.128853f;
	}
	else
	{
		targetR = 0.875f;
		targetG = 0.733709f;
		targetB = 0.112746f;
	}
}

void UStanceGaugeWidget_D::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Irene == nullptr) return;

	auto Current = Irene->IreneData.CurrentGauge;

	BrushSetColor(Current);

	auto MAT = gauge_full->GetDynamicMaterial();
	MAT->SetScalarParameterValue("Progress", Current / 100.0f);

	/*if (SHINE)
	{
		FLinearColor c;
		MAT->GetVectorParameterValue(FHashedMaterialParameterInfo(), c);
		auto R = UKismetMathLibrary::FInterpTo(c.R, targetR, InDeltaTime, 10.0f);
		auto G = UKismetMathLibrary::FInterpTo(c.G, targetG, InDeltaTime, 10.0f);
		auto B = UKismetMathLibrary::FInterpTo(c.B, targetB, InDeltaTime, 10.0f);
		MAT->SetVectorParameterValue("ProgressColor1", FLinearColor(R, G, B));
	}*/
}
