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
	TSubclassOf<class UKeySetWidget> KeySetWidgetClass;
	class UKeySetWidget* KeySetWidget;

	//사운드세팅 위젯
	TSubclassOf<class USoundSettingWidget> SoundSetWidgetClass;
	class USoundSettingWidget* SoundSetWidget;
	
public:

	UFUNCTION(BlueprintCallable)
	void WidgetOn();
	UFUNCTION(BlueprintCallable)
	 void WidgetOff();


	virtual void NativeConstruct() override;

	//키세팅 위젯
	UFUNCTION(BlueprintCallable)
	void KeySetWidgetOn();

	//사운드세팅 위젯
	UFUNCTION(BlueprintCallable)
	void SoundSetWidgetOn();
};
