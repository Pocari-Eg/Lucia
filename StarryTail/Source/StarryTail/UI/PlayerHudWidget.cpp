// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/IreneUIManager.h"
#include"../PlayerSource/IreneAttackInstance.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//���ε��� object�� CurrentObject�� �Ҵ�
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//��������Ʈ�� ���� UpdateWidget�Լ��� ȣ��ɼ� �ֵ��� 

	NewIrene->IreneUIManager->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	NewIrene->IreneUIManager->OnStaminaChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
	NewIrene->FOnAttributeChange.AddUObject(this, &UPlayerHudWidget::UpdateAttributes);
}

void UPlayerHudWidget::SetDialog(FString dialog)
{
	DialogText=dialog;
}

void UPlayerHudWidget::PlayDialog()
{
	DialogWidget->SetDialog(*DialogText);
}

void UPlayerHudWidget::RaidWidgetbind(AMonster* RadiMonster)
{
	RMWidget->BindMonster(RadiMonster);
}

void UPlayerHudWidget::UpdateHp()
{
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
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
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
	if (CurrentIrene != nullptr)
	{
		if (nullptr != MPProgressBar)
		{
			MPProgressBar->SetPercent(CurrentIrene->IreneUIManager->GetStaminaRatio());
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


void UPlayerHudWidget::UpdateAttributes()
{
	switch (CurrentIrene->IreneAttack->GetAttribute())
	{
	case EAttributeKeyword::e_None:
		 FireSetScale(BaseScale);
		 WaterSetScale(BaseScale);
		 ElectricSetScale(BaseScale);
		break;
	case EAttributeKeyword::e_Fire:
		
		FireSetScale(SelectScale);
		WaterSetScale(BaseScale);
		ElectricSetScale(BaseScale);
		
		break;
	case EAttributeKeyword::e_Water:
		
		FireSetScale(BaseScale);
		WaterSetScale(SelectScale);
		ElectricSetScale(BaseScale);
		break;
	case EAttributeKeyword::e_Thunder:
		
		FireSetScale(BaseScale);
		WaterSetScale(BaseScale);
		ElectricSetScale(SelectScale);
		break;
	}
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

void UPlayerHudWidget::ActionWidgetOn()
{
	ActionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerHudWidget::ActionWidgetOff()
{
	ActionWidget->SetVisibility(ESlateVisibility::Hidden);
}



void UPlayerHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("Init"));
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
	HPRecoveryProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_RecoverBar")));

	DialogWidget = Cast<UDialogWidget>(GetWidgetFromName(TEXT("BP_DialogWidget")));
	RMWidget = Cast<URaidMonsterWidget>(GetWidgetFromName(TEXT("BP_RaidMonsterWidget")));
	ActionWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("BP_ActionWidget")));
	RMWidget->SetVisibility(ESlateVisibility::Hidden);


	ActionWidgetOff();

}
