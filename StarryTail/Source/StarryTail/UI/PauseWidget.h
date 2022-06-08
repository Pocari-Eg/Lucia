// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:

	//키세팅 위젯
	class UKeySetWidget* KeySetWidget;
	//사운드세팅 위젯
	class USoundSettingWidget* SoundSetWidget;

	UPROPERTY()
	class UButton* ResumButton;
	UPROPERTY()
	class UButton* SoundWidgetButton;
	UPROPERTY()
	class UButton* QuitButton;

public:

	bool bIsEnableResume;

public:

	UFUNCTION(BlueprintCallable)
	void WidgetOn();
	UFUNCTION(BlueprintCallable)
	bool WidgetOff();

	//키세팅 위젯
	UFUNCTION(BlueprintCallable)
	void KeySetWidgetOn();

	//사운드세팅 위젯
	UFUNCTION(BlueprintCallable)
	void SoundSetWidgetOn();
	UFUNCTION(BlueprintCallable)
	void ExitWidgetOn();

	void DisableButton();
	void EnableButton();

protected:
	virtual void NativeOnInitialized() override;
};
