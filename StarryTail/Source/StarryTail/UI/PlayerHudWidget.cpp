// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "../PlayerSource/IreneCharacter.h"
#include "Components/ProgressBar.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//새로들어온 object를 CurrentObject에 할당
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 

	NewIrene->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	NewIrene->OnMpChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
}

void UPlayerHudWidget::UpdateHp()
{
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentIrene != nullptr)
	{
	
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentIrene->GetHpRatio());
		}
	}
	UpdateHpRecovery();
	
}

void UPlayerHudWidget::UpdateMp()
{
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentIrene != nullptr)
	{
		if (nullptr != MPProgressBar)
		{
			MPProgressBar->SetPercent(CurrentIrene->GetMpRatio());
		}
	}
}

void UPlayerHudWidget::UpdateHpRecovery()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != HPRecoveryProgressBar)
		{
			HPRecoveryProgressBar->SetPercent(CurrentIrene->GetHpRecoveryRatio());
		}
	}
}

void UPlayerHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("Init"));
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
	HPRecoveryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_RecoverBar")));
}
