// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "PauseWidget.h"

#include "../SoundManager.h"
#include "../STGameInstance.h"

#include "Components/CheckBox.h"
#include "Components/Slider.h"

#include "SoundSettingWidget.generated.h"

/**
 * 
 */

USTRUCT(Atomic)
struct FSoundWidget
{
	GENERATED_BODY()
	UPROPERTY()
	class UCheckBox* CheckBox;
	UPROPERTY()
	class USlider* Slider;
};
UCLASS()
class STARRYTAIL_API USoundSettingWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPauseWidget* PauseWidget;

	FSoundWidget SFXWidget;
	FSoundWidget BGMWidget;

public:
	UFUNCTION(BlueprintCallable)
	void WidgetOn(UPauseWidget* widget);
	UFUNCTION(BlueprintCallable)
	void WidgetOff();

protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
private:
	void SoundWidgetSet();
	void SoundSettingSave();
};
