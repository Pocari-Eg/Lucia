// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../SoundManager.h"
#include "PauseWidget.h"
#include "SoundSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API USoundSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPauseWidget* PauseWidget;
public:
	UFUNCTION(BlueprintCallable)
	void WidgetOn(UPauseWidget* widget);
	UFUNCTION(BlueprintCallable)
	void WidgetOff();
};
