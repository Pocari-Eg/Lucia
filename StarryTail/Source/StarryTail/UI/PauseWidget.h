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
	TSubclassOf<class UKeySetWidget> KeySetWidgetClass;
	class UKeySetWidget* KeySetWidget;
	
public:

	UFUNCTION(BlueprintCallable)
	void WidgetOn();
	UFUNCTION(BlueprintCallable)
	 void WidgetOff();


	virtual void NativeConstruct() override;

	//Ű���� ����
	UFUNCTION(BlueprintCallable)
	void KeySetWidgetOn();
};
