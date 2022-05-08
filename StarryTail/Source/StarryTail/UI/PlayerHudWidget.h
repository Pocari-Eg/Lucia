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
	//속성 관련 데이터
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
	// Player 바인드 할떄 사용 
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
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
private:

	//현재 오브젝트
	class AIreneCharacter* CurrentIrene;
	//위젯 안 HP Bar 데이터
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
