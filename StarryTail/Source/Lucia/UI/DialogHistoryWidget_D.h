// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogHistoryWidget_D.generated.h"

UCLASS()
class LUCIA_API UDialogHistoryWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void DialogueStart(class UDataTable* table, FName startName, FName endName);

	void SettingWidgetAnimation();

	UFUNCTION(BlueprintCallable)
	void nextTalk();
	UFUNCTION(BlueprintCallable)
	void trySkipDialogue();

public:
	UPROPERTY(EditAnyWhere)
	TSubclassOf<class UUserWidget> ChildWidget_C;
	UPROPERTY(EditAnyWhere)
	class UScrollBox* DialgoueScroll;
	UPROPERTY(EditAnyWhere)
	class UImage* A_1;
	UPROPERTY(EditAnyWhere)
	class UImage* A_2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool CanNextTalk;

	class ADialogHistoryTrigger* Owner;

	UPROPERTY(EditAnyWhere)
	class UCanvasPanel* DialogueHistoryCanvas;

	FText lastTalkingPerson;

	UPROPERTY()
	class UTextBlock* TextBlock_B1;

	class UDataTable* dialogueTable;
	TArray<FName> dialogueArr;
	int32 dialogueIndex;

	TArray<UWidgetAnimation*> widgetAnimArr;
	// 0 : FadeIn_A1 , 1 : FadeIn_A2 , 2 : Disable_A1 , 3 : Disable_A2
};
