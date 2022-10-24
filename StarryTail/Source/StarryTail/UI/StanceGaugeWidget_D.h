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

public:
	UFUNCTION(BlueprintCallable)
	void eCtime(float Ctime);

	void ResetStanceGague();

	void eCtimeflow();
};
