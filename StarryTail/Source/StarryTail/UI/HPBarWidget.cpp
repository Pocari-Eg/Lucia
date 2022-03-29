// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../Object/TestObject.h"
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
}


void UHPBarWidget::UpdateWidget(float Hp)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetPercent(Hp);
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

void UHPBarWidget::SetColor(FLinearColor Color)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetFillColorAndOpacity(Color);
	}
}
