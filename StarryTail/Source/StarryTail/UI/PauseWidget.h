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

	//Ű���� ����
	class UKeySetWidget* KeySetWidget;

	//���弼�� ����
	class USoundSettingWidget* SoundSetWidget;

public:
	bool IsKeySetWidgetOn;
	bool IsSoundSetwidgetOn;
	
public:

	UFUNCTION(BlueprintCallable)
	void WidgetOn();
	UFUNCTION(BlueprintCallable)
	bool WidgetOff();



	//Ű���� ����
	UFUNCTION(BlueprintCallable)
	void KeySetWidgetOn();

	//���弼�� ����
	UFUNCTION(BlueprintCallable)
	void SoundSetWidgetOn();

protected:
	virtual void NativeOnInitialized() override;
};
