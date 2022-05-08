// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "DialogWidget.h"


#include "PlayerHudWidget.generated.h"

/**
 * 
 */


USTRUCT()
struct FAttributesUI
{
	GENERATED_BODY()
	//�Ӽ� ���� ������
	UPROPERTY()
	class UImage* Attribute;
	UPROPERTY()
	class UProgressBar* Base;
	UPROPERTY()
	class UProgressBar* Recovery;
};
UCLASS()
class STARRYTAIL_API UPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Player ���ε� �ҋ� ��� 
	void BindCharacter(class AIreneCharacter* NewIrene);


private:

	void UpdateHp();
	void UpdateMp();
	void UpdateHpRecovery();

	void UpdateAttributes();

	//fire
	void UpdateFire();
	void UpdateFireRecovery();

	//Water
	void UpdateWater();
	void UpdateWaterRecovery();

	//Electric
	void UpdateEeletric();
	void UpdateEeletricRecovery();

	void NoneSetScale(FVector2D Scale);
	void FireSetScale(FVector2D Scale);
	void WaterSetScale(FVector2D Scale);
	void ElectricSetScale(FVector2D Scale);
protected:
	// ������ �ʱ�ȭ
	virtual void NativeOnInitialized() override;
private:

	//���� ������Ʈ
	class AIreneCharacter* CurrentIrene;
	//���� �� HP Bar ������
	UPROPERTY()
	class UProgressBar* HPProgressBar;
	UPROPERTY()
	class UProgressBar* HPRecoveryProgressBar;
	UPROPERTY()
	class UProgressBar* MPProgressBar;	

	UPROPERTY()
	class UDialogWidget* DialogWidget;

	FAttributesUI None;
	FAttributesUI Fire;
	FAttributesUI Water;
	FAttributesUI Electric;

	FVector2D BaseScale= FVector2D(1.0f, 1.0f);
	FVector2D SelectScale = FVector2D(1.5f, 1.5f);

};
