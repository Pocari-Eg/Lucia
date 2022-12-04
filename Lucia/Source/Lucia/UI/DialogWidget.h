// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
#include "Blueprint/UserWidget.h"
#include "ScriptDataTable.h"

#include "Components/TextBlock.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Time)
	float TextPrintTime;
	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = Time)
	float TextKeepTime;
	//출력용 변수
	UPROPERTY(BluePrintReadOnly)
	FString OutputDialog;
protected:

	
private:
	//전송된 메시지를 담는 변수
	FString InputDialog;

	//현재까지 출력된 메시지의 길이
	int32 Length;
	FTimerHandle TimerHandle; // TimerHandle;
	
	class UTextBlock* TextBox;

	UObject* Font;

	EDialogState CurrnetState;

	float CurrentTextKeeptime;

	class UPlayerHudWidget* PlayerHud;
public:
	//출력할 메시지 세팅
	void SetDialog(FScriptData* ScriptData);
	void PassDialog();
	void EndDialog();

	EDialogState GetDialogState();
	void SetDialogState(EDialogState NewState);

	void BindPlayerHud(class UPlayerHudWidget* NewPlayerHud);

	UFUNCTION(BlueprintImplementableEvent)
	void  OnPopUpIrene();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnPopUpNox();

	UFUNCTION(BlueprintImplementableEvent)
	void  OnNormalIrene();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnNormalNox();
	UFUNCTION(BlueprintImplementableEvent)
	void  OnNormalNone();


	void DialogTimerClear();
protected:
	virtual void NativeConstruct() override;
private:
	//메시지 재생
	void PlayDialog();
	void PlayPopUpDialog();
};
