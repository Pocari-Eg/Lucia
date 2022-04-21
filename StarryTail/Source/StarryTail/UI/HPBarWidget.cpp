// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../Object/TestObject.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::BindObjectHp(class ATestObject* NewObject)
{
	//새로들어온 object를 CurrentObject에 할당
	CurrentObject = Cast<ATestObject>(NewObject);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 
	// NewObject->OnHpChanged.AddUObject(this, &UHPBarWidget::UpdateWidget);
	

}

void UHPBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	DefProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("DefBar")));
	MarkerImage = Cast<UImage>(GetWidgetFromName(TEXT("Marker")));
}


void UHPBarWidget::UpdateHpWidget(float UpdateHp)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetPercent(UpdateHp);
	}
	/*
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentObject != nullptr)
	{
		if (nullptr != HPProgressBar)
		{
				HPProgressBar->SetPercent(Object->GetHpRatio());
		}
	}
	*/
}

void UHPBarWidget::UpdateDefWidget(float Def)
{

	if (nullptr != DefProgressBar)
	{
		DefProgressBar->SetPercent(Def);
	}
}

void UHPBarWidget::SetColor(FLinearColor Color)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetFillColorAndOpacity(Color);
	}
}

void UHPBarWidget::MarkerOnOff()
{
	
	if (MarkerImage->IsVisible())MarkerImage->SetVisibility(ESlateVisibility::Hidden);
	else MarkerImage->SetVisibility(ESlateVisibility::Visible);
}
