// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StanceGaugeWidget_D.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UStanceGaugeWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UImage* gauge_full;

	UMaterialInstanceDynamic* mat_Progress;
	FTimerHandle AttackCtimeHandle;
	float PLUS = 0.0f;

	float Timer, maxTimer;

	class AIreneCharacter* Irene;

public:
	UFUNCTION(BlueprintCallable)
	void eCtime(float Ctime);
	UFUNCTION(BlueprintCallable)
	void ResetStanceGague();

	UFUNCTION(BlueprintCallable)
	void SetCoolTime(float Time);

	void eCtimeflow();

	virtual void NativeConstruct() override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
};
