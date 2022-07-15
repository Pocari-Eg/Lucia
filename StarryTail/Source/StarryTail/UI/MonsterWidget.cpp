// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterWidget.h"
#include "../EnemySource/Monster.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UMonsterWidget::BindMonster(class AMonster* NewMonster)
{
	
	//새로들어온 Monster를 CurrentMonster에 할당
	CurrentMonster = Cast<AMonster>(NewMonster);

	if (CurrentMonster->GetRank() == EEnemyRank::e_Raid)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {

		//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 
		CurrentMonster->OnHpChanged.AddUObject(this, &UMonsterWidget::UpdateHpWidget);
		CurrentMonster->OnBarrierChanged.AddUObject(this, &UMonsterWidget::UpdateDefWidget);

		if (CurrentMonster->GetRank() == EEnemyRank::e_Common)
		{
			//DefProgressBar->SetVisibility(ESlateVisibility::Hidden);
			//DefLine->SetVisibility(ESlateVisibility::Hidden);

			OnBarrierUI();
		}
	}
}



void UMonsterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBar")));
	DefProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("DefBar")));
	MarkerImage = Cast<UImage>(GetWidgetFromName(TEXT("Marker")));
     HPLine = Cast<UImage>(GetWidgetFromName(TEXT("HPBar_Line")));
	 DefLine = Cast<UImage>(GetWidgetFromName(TEXT("DefBar_Line")));
}


void UMonsterWidget::UpdateHpWidget()
{


	if (CurrentMonster != nullptr)
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentMonster->GetHpRatio());
		}
	}
	
}

void UMonsterWidget::UpdateDefWidget()
{
	if (CurrentMonster->GetRank() == EEnemyRank::e_Common)
	{
		OnBarrierAttributeChange();
	}
	if (CurrentMonster != nullptr)
	{
		if (nullptr != DefProgressBar)
		{
			DefProgressBar->SetPercent(CurrentMonster->GetDefRatio());
		}
	}
}

void UMonsterWidget::SetColor(FLinearColor Color)
{
	if (nullptr != HPProgressBar)
	{
		HPProgressBar->SetFillColorAndOpacity(Color);
	}
}

void UMonsterWidget::MarkerOn()
{
	MarkerImage->SetVisibility(ESlateVisibility::Visible);
}

void UMonsterWidget::MarkerOff()
{
	MarkerImage->SetVisibility(ESlateVisibility::Hidden);
}

EAttributeKeyword UMonsterWidget::GetBarrierAttribute()
{

	return CurrentMonster->GetBarrierAttribute();
}
