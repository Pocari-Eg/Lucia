// Fill out your copyright notice in the Description page of Project Settings.


#include "RaidMonsterWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
void URaidMonsterWidget::BindMonster(class AMonster* Monster) {

	CurrentBoss = Monster;


	CurrentBoss->OnHpChanged.AddUObject(this, &URaidMonsterWidget::UpdateHp);
	CurrentBoss->OnBarrierChanged.AddUObject(this, &URaidMonsterWidget::UpdateShield);
	STARRYLOG_S(Warning);
}

void URaidMonsterWidget::UpdateHp()
{

	if (CurrentBoss != nullptr)		
	{
	
		if (HPProgressBar != nullptr)
		{
			
			HPProgressBar->SetPercent(CurrentBoss->GetHpRatio());
		}
	}
	
}

void URaidMonsterWidget::UpdateShield()
{
	if (CurrentBoss != nullptr)
	{
		if (ShieldBar != nullptr)
		{
			
			ShieldBar->SetPercent(CurrentBoss->GetDefRatio());
		}
	}
}







void URaidMonsterWidget::NativeConstruct()
{
	
	 HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_HPBar")));
	 ShieldBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("RM_ShieldBar")));
}

