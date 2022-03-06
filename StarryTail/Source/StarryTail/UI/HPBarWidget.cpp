// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../TestObject.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::BindObjectHp(class ATestObject* NewObject)
{
	//새로들어온 object를 CurrentObject에 할당
	CurrentObject = NewObject;

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 
	NewObject->OnHpChanged.AddUObject(this, &UHPBarWidget::UpdateWidget);

}

void UHPBarWidget::NativeConstruct()
{
	//BP_HpBarWidget에 HPBar를 불러온다
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	//첫 위젯 상태 업데이트
	UpdateWidget();
}

void UHPBarWidget::UpdateWidget()
{
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentObject != nullptr)
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentObject->GetHpRatio());
		}
	}
}
