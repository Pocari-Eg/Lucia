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

void UHPBarWidget::NativeConstruct()
{
	//BP_HpBarWidget�� HPBar�� �ҷ��´�
	Super::NativeConstruct();

	
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	/*
	//ù ���� ���� ������Ʈ
	UpdateWidget();
	*/
}

void UHPBarWidget::UpdateWidget(float Hp)
{
	HPProgressBar->SetPercent(Hp);
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
