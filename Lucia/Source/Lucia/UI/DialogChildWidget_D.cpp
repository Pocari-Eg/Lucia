// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogChildWidget_D.h"
#include "DialogHistoryWidget_D.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"

void UDialogChildWidget_D::DefaultSetting(UDialogHistoryWidget_D* _owner, FString _dialogue)
{
	owner = _owner;
	dialogueVariable = _dialogue;

	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	widgetAnimArr.Empty();

	for (int i = 0; i < WidgetClass->Animations.Num(); i++) {

		FString Name = WidgetClass->Animations[i]->GetName();
		widgetAnimArr.Add(WidgetClass->Animations[i]);
	}
}

void UDialogChildWidget_D::SetTalkPerson(bool talkOthersPerson)
{
	if (talkOthersPerson)
	{
		B_1->SetBrushFromTexture(OtherPersonSkin);
		PlayAnimation(widgetAnimArr[1]);
		DialogueBlock->SetRenderTranslation(FVector2D(-100.0f, 0.0f));
		return;
	}
	
	DialogueBlock->SetRenderTranslation(FVector2D(-50.0f, 0.0f));
	PlayAnimation(widgetAnimArr[0]);
}

void UDialogChildWidget_D::DialgoueStart()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(dialgoueHandle)) return;

	GetWorld()->GetTimerManager().SetTimer(dialgoueHandle, this, &UDialogChildWidget_D::nextTypingDialogue, 0.1f, true);
}

void UDialogChildWidget_D::nextTypingDialogue()
{
	dialgoueIndex++;
	if (dialogueVariable.Len() < dialgoueIndex)
	{
		GetWorld()->GetTimerManager().ClearTimer(dialgoueHandle);
		return;
	}

	DialogueBlock->SetText(FText::FromString(dialogueVariable.Left(dialgoueIndex)));
}

bool UDialogChildWidget_D::IsHandleActive()
{
	return GetWorld()->GetTimerManager().IsTimerActive(dialgoueHandle);
}

void UDialogChildWidget_D::tryDiableDialgoue()
{
	PlayAnimation(widgetAnimArr[2]);
}

void UDialogChildWidget_D::SkipDialogue()
{
	if (!IsHandleActive()) return;

	GetWorld()->GetTimerManager().ClearTimer(dialgoueHandle);
	DialogueBlock->SetText(FText::FromString(dialogueVariable));
}
