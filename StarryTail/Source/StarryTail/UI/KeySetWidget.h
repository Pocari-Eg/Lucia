// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.h"

#include "KeySetWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UKeySetWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPauseWidget* PauseWidget;
	FKey NONE;

	
public:
	UFUNCTION(BlueprintCallable)
	void WidgetOn(UPauseWidget* widget);
	UFUNCTION(BlueprintCallable)
	 void WidgetOff();

	UFUNCTION(BlueprintCallable)
	void ChangeKey(const FName ActionName, UPARAM(ref) FInputChord& InputKey);
	UFUNCTION(BlueprintCallable)
	void UpdateKeyName(UPARAM(ref) TArray<UInputKeySelector*>& InputKey);
	UPROPERTY(BluePrintReadOnly)
	bool IsEmptyKey;
	UPROPERTY(BluePrintReadOnly)
	bool IsUpdatekey;
};
