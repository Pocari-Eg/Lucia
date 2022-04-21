// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../Object/TestObject.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::BindObjectHp(class ATestObject* NewObject)
{
	//���ε��� object�� CurrentObject�� �Ҵ�
	CurrentObject = Cast<ATestObject>(NewObject);

	//��������Ʈ�� ���� UpdateWidget�Լ��� ȣ��ɼ� �ֵ��� 
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
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
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
