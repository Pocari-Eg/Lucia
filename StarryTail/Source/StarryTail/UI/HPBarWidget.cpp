// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../Object/TestObject.h"
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
}


void UHPBarWidget::UpdateWidget(float Hp)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetPercent(Hp);
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

void UHPBarWidget::SetColor(FLinearColor Color)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetFillColorAndOpacity(Color);
	}
}
