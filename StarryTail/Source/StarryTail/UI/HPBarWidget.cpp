// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../EnemySource/Monster.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::BindMonster(class AMonster* NewMonster)
{
	//새로들어온 Monster를 CurrentMonster에 할당
	CurrentMonster = Cast<AMonster>(NewMonster);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 
	CurrentMonster->OnHpChanged.AddUObject(this, &UHPBarWidget::UpdateHpWidget);
	CurrentMonster->OnDefChanged.AddUObject(this, &UHPBarWidget::UpdateDefWidget);

	if (CurrentMonster->GetRank() == EEnemyRank::e_Common)
	{
		DefProgressBar->SetVisibility(ESlateVisibility::Hidden);
		DefLine->SetVisibility(ESlateVisibility::Hidden);
	}

}



void UHPBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	DefProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("DefBar")));
	MarkerImage = Cast<UImage>(GetWidgetFromName(TEXT("Marker")));
     HPLine = Cast<UImage>(GetWidgetFromName(TEXT("HPBar_Line")));
	 DefLine = Cast<UImage>(GetWidgetFromName(TEXT("DefBar_Line")));
}


void UHPBarWidget::UpdateHpWidget()
{


	if (CurrentMonster != nullptr)
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentMonster->GetHpRatio());
		}
	}
	
}

void UHPBarWidget::UpdateDefWidget()
{

	
	if (CurrentMonster != nullptr)
	{
		if (nullptr != DefProgressBar)
		{
			DefProgressBar->SetPercent(CurrentMonster->GetDefRatio());
		}
	}
}

void UHPBarWidget::SetColor(FLinearColor Color)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetFillColorAndOpacity(Color);
	}
}

void UHPBarWidget::MarkerOn()
{
	MarkerImage->SetVisibility(ESlateVisibility::Visible);
}

void UHPBarWidget::MarkerOff()
{
	MarkerImage->SetVisibility(ESlateVisibility::Hidden);
}