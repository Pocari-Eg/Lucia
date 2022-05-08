// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/IreneUIManager.h"
#include"../PlayerSource/IreneAttackInstance.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//새로들어온 object를 CurrentObject에 할당
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//델리게이트를 통해 UpdateWidget함수가 호출될수 있도록 

	NewIrene->IreneUIManager->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	NewIrene->IreneUIManager->OnMpChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
	NewIrene->FOnAttributeChange.AddUObject(this, &UPlayerHudWidget::UpdateAttributes);
	NewIrene->IreneAttack->FOnFireGaugeChange.AddUObject(this, &UPlayerHudWidget::UpdateFire);
	NewIrene->IreneAttack->FOnWaterGaugeChange.AddUObject(this, &UPlayerHudWidget::UpdateWater);
	NewIrene->IreneAttack->FOnElectricGaugeChange.AddUObject(this, &UPlayerHudWidget::UpdateEeletric);

}

void UPlayerHudWidget::UpdateHp()
{
	//오브젝트랑 위젯이 비어있지 않은지 확인후 HPBar의 퍼센티지 갱신
	if (CurrentIrene != nullptr)
	{
	
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRatio());
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
			MPProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetMpRatio());
		}
	}
}

void UPlayerHudWidget::UpdateHpRecovery()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != HPRecoveryProgressBar)
		{
			HPRecoveryProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetHpRecoveryRatio());
		}
	}
}

void UPlayerHudWidget::UpdateFire()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Fire.Base)
		{
			//Fire.Base->SetPercent(CurrentIrene->IreneAttack->GetFireRatio());
		}
	}
	//UpdateFireRecovery();
}

void UPlayerHudWidget::UpdateFireRecovery()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Fire.Recovery)
		{
			//Fire.Recovery->SetPercent(CurrentIrene->IreneAttack->GetFireRecoveryRatio());
		}
	}
}

void UPlayerHudWidget::UpdateWater()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Water.Base)
		{
			//Water.Base->SetPercent(CurrentIrene->IreneAttack->GetWaterRatio());
		}
	}
	//UpdateWaterRecovery();
}

void UPlayerHudWidget::UpdateWaterRecovery()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Water.Recovery)
		{
			//Water.Recovery->SetPercent(CurrentIrene->IreneAttack->GetWaterRecoveryRatio());
		}
	}
}

void UPlayerHudWidget::UpdateEeletric()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Electric.Base)
		{
			//Electric.Base->SetPercent(CurrentIrene->IreneAttack->GetElectricRatio());
		}
	}
	//UpdateEeletricRecovery();
}

void UPlayerHudWidget::UpdateEeletricRecovery()
{
	if (CurrentIrene != nullptr)
	{

		if (nullptr != Electric.Recovery)
		{
			//Electric.Recovery->SetPercent(CurrentIrene->IreneAttack->GetElectricRecoveryRatio());
		}
	}
}


void UPlayerHudWidget::UpdateAttributes()
{
	FString text = TEXT("당근을 흔들어 주세요...");
	DialogWidget->SetDialog(*text);
	switch (CurrentIrene->IreneAttack->GetAttribute())
	{
	case EAttributeKeyword::e_None:
		 NoneSetScale(SelectScale);
		 FireSetScale(BaseScale);
		 WaterSetScale(BaseScale);
		 ElectricSetScale(BaseScale);
		break;
	case EAttributeKeyword::e_Fire:
		NoneSetScale(BaseScale);
		FireSetScale(SelectScale);
		WaterSetScale(BaseScale);
		ElectricSetScale(BaseScale);
		
		break;
	case EAttributeKeyword::e_Water:
		NoneSetScale(BaseScale);
		FireSetScale(BaseScale);
		WaterSetScale(SelectScale);
		ElectricSetScale(BaseScale);
		break;
	case EAttributeKeyword::e_Thunder:
		NoneSetScale(BaseScale);
		FireSetScale(BaseScale);
		WaterSetScale(BaseScale);
		ElectricSetScale(SelectScale);
		break;
	}
}



void UPlayerHudWidget::NoneSetScale(FVector2D Scale)
{
	None.Attribute->SetRenderScale(Scale);
	None.Base->SetRenderScale(Scale);

}

void UPlayerHudWidget::FireSetScale(FVector2D Scale)
{
	Fire.Attribute->SetRenderScale(Scale);
	Fire.Base->SetRenderScale(Scale);
}

void UPlayerHudWidget::WaterSetScale(FVector2D Scale)
{
	Water.Attribute->SetRenderScale(Scale);
	Water.Base->SetRenderScale(Scale);
}

void UPlayerHudWidget::ElectricSetScale(FVector2D Scale)
{
	Electric.Attribute->SetRenderScale(Scale);
	Electric.Base->SetRenderScale(Scale);

	
}



void UPlayerHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("Init"));
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
	HPRecoveryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_RecoverBar")));

	//속성
	 None.Attribute= Cast<UImage>(GetWidgetFromName(TEXT("NoneUi")));
	 None.Base = Cast<UProgressBar>(GetWidgetFromName(TEXT("NoneBase")));
	 None.Recovery = Cast<UProgressBar>(GetWidgetFromName(TEXT("NoneBase")));

	 Fire.Attribute = Cast<UImage>(GetWidgetFromName(TEXT("fire")));
	 Fire.Base = Cast<UProgressBar>(GetWidgetFromName(TEXT("FireBase")));
	 Fire.Recovery = Cast<UProgressBar>(GetWidgetFromName(TEXT("FireRecovery")));

	 Water.Attribute = Cast<UImage>(GetWidgetFromName(TEXT("water")));
	 Water.Base = Cast<UProgressBar>(GetWidgetFromName(TEXT("WaterBase")));
	 Water.Recovery = Cast<UProgressBar>(GetWidgetFromName(TEXT("WaterRecovery")));

	 Electric.Attribute = Cast<UImage>(GetWidgetFromName(TEXT("Electric")));
	 Electric.Base = Cast<UProgressBar>(GetWidgetFromName(TEXT("ElectricBase")));
	 Electric.Recovery = Cast<UProgressBar>(GetWidgetFromName(TEXT("ElectricRecovery")));

	DialogWidget = Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_DialogWidget")));

	 NoneSetScale(SelectScale);
}
