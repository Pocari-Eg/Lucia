// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.h"
#include "Components/InputKeySelector.h"
#include "KeySetWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UKeySetWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	UPauseWidget* PauseWidget;
	FKey NONE;

	UPROPERTY()
	class UButton* BackButton;

public:
	UPROPERTY(BluePrintReadOnly)
	bool IsActionEmptyKey;

	UPROPERTY(BluePrintReadOnly)
	bool IsAxisEmptyKey;
	UPROPERTY(BluePrintReadOnly)
	bool IsUpdatekey;

	

public:

	UFUNCTION(BluePrintcallable)
	void WidgetOff();

	UFUNCTION(BlueprintCallable)
	void ChangeActionKey(const FName ActionName, UPARAM(ref) FInputChord& InputKey);

	UFUNCTION(BlueprintCallable)
		void ChangeAxisKey(const FName AxisName, UPARAM(ref) FInputChord& InputKey);
	UFUNCTION(BlueprintCallable)
		void UpdateActionKeyName();

	UFUNCTION(BlueprintCallable)
		void UpdateAxisKeyName();
	UPROPERTY(BlueprintReadWrite);
	TArray<class UInputKeySelector*> InputActionKeyArray;

	UPROPERTY(BlueprintReadWrite);
	TArray<class UInputKeySelector*> InputAxisKeyArray;

	void SetExitEnable();

	void BindPauseWidget(UPauseWidget* CurrentWidget);
protected:
	// ������ �ʱ�ȭ
	virtual void NativeConstruct() override;
};
