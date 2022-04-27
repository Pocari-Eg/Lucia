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

	//虐技泼 困连
	TSubclassOf<class UKeySetWidget> KeySetWidgetClass;
	class UKeySetWidget* KeySetWidget;
	
public:

	UFUNCTION(BlueprintCallable)
	void WidgetOn();
	UFUNCTION(BlueprintCallable)
	 void WidgetOff();


	virtual void NativeConstruct() override;

	//虐技泼 困连
	UFUNCTION(BlueprintCallable)
	void KeySetWidgetOn();
};
