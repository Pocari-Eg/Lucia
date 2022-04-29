// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.h"
#include "Components/InputKeySelector.h"
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
	UPROPERTY(BluePrintReadOnly)
	bool IsEmptyKey;
	UPROPERTY(BluePrintReadOnly)
	bool IsUpdatekey;

	UPROPERTY()
	class UButton* ExitButton;
public:


	UFUNCTION(BlueprintCallable)
		void WidgetOn(UPauseWidget* widget);
	UFUNCTION(BlueprintCallable)
		void WidgetOff();

	UFUNCTION(BlueprintCallable)
		void ChangeKey(const FName ActionName, UPARAM(ref) FInputChord& InputKey);
	UFUNCTION(BlueprintCallable)
		void UpdateKeyName();
	UPROPERTY(BlueprintReadWrite);
	TArray<class UInputKeySelector*> InputKeyArray;

	void SetExitEnable();
protected:
	// 위젯을 초기화
	virtual void NativeOnInitialized() override;
};
