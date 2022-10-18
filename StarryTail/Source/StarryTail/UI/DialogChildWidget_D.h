// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogChildWidget_D.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UDialogChildWidget_D : public UUserWidget
{
	GENERATED_BODY()

public:
	void DefaultSetting(class UDialogHistoryWidget_D* _owner, FString _dialogue);
	void SetTalkPerson(bool talkOthersPerson);

	bool IsHandleActive();
	void tryDiableDialgoue();

	void DialgoueStart();
	void nextTypingDialogue();
	void SkipDialogue();

public:
	UPROPERTY(EditAnyWhere)
	UTexture2D* OtherPersonSkin;

	UPROPERTY()
	class UImage* B_1;
	UPROPERTY()
	class UTextBlock* DialogueBlock;

	class UDialogHistoryWidget_D* owner;
	FString dialogueVariable;

	FTimerHandle dialgoueHandle;
	int32 dialgoueIndex;

	TArray<UWidgetAnimation*> widgetAnimArr;
	// 0 : Talking_Type1 , 1 : Talking_Type2 , 2 : DisableDialogue
};
