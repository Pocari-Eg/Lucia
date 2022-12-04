// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UltimateGaugeWidget_D.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UUltimateGaugeWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class UProgressBar* ultimate_fillBar;
	UPROPERTY()
	class UImage* ultimate_fill;

	UPROPERTY(EditAnyWhere)
	FLinearColor normal;
	UPROPERTY(EditAnyWhere)
	FLinearColor Fill;
	UPROPERTY(EditAnyWhere)
	FLinearColor full;

public:
	UFUNCTION(BlueprintCallable)
	void SetUltimate(float pErcent);
	UFUNCTION(BlueprintCallable)
	void SetUltimateBlueprint(float pErcent);

	void SetColors(float _current);

	
};
