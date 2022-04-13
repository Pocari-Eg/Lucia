// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "Components/ProgressBar.h"

void UPlayerHudWidget::BindCharacter(class AIreneCharacter* NewIrene) {

	//���ε��� object�� CurrentObject�� �Ҵ�
	CurrentIrene = Cast<AIreneCharacter>(NewIrene);

	//��������Ʈ�� ���� UpdateWidget�Լ��� ȣ��ɼ� �ֵ��� 

	NewIrene->OnHpChanged.AddUObject(this, &UPlayerHudWidget::UpdateHp);
	NewIrene->OnMpChanged.AddUObject(this, &UPlayerHudWidget::UpdateMp);
}

void UPlayerHudWidget::UpdateHp()
{
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
	if (CurrentIrene != nullptr)
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentIrene->GetHpRatio());
		}
	}
	
}

void UPlayerHudWidget::UpdateMp()
{
	//������Ʈ�� ������ ������� ������ Ȯ���� HPBar�� �ۼ�Ƽ�� ����
	if (CurrentIrene != nullptr)
	{
		if (nullptr != MPProgressBar)
		{
			MPProgressBar->SetPercent(CurrentIrene->GetMpRatio());
		}
	}
	
}

void UPlayerHudWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_Bar")));
	MPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_Bar")));
}
