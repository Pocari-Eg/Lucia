// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHistoryWidget_D.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Kismet/KismetArrayLibrary.h"
#include "ScriptDataTable.h"
#include "DialogChildWidget_D.h"
#include "../PlayerSource/PlayerInstance/IreneUIManager.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../Object/Trigger/DialogHistoryTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"

void UDialogHistoryWidget_D::DialogueStart(UDataTable* table, FName startName, FName endName)
{
	if (table == nullptr) return;

	dialogueArr.Empty();
	dialogueIndex = 0;
	dialogueTable = table;
	lastTalkingPerson = FText::FromString(TEXT("NONE"));

	TArray<FName> getName;
	UDataTableFunctionLibrary::GetDataTableRowNames(table, getName);
	bool saveStart = false;

	for (auto forTableName : getName)
	{
		if (forTableName == startName) saveStart = true;

		if (saveStart) dialogueArr.Add(forTableName);

		if (forTableName == endName) saveStart = false;
	}

	SettingWidgetAnimation();

	PlayAnimation(widgetAnimArr[0]);
	PlayAnimation(widgetAnimArr[1]);
}

void UDialogHistoryWidget_D::SettingWidgetAnimation()
{
	UWidgetBlueprintGeneratedClass* WidgetClass = GetWidgetTreeOwningClass();

	widgetAnimArr.Empty();

	for (int i = 0; i < WidgetClass->Animations.Num(); i++) {

		FString Name = WidgetClass->Animations[i]->GetName();
		widgetAnimArr.Add(WidgetClass->Animations[i]);
	}
}

void UDialogHistoryWidget_D::nextTalk()
{
	if (!CanNextTalk) return;

	auto Player = Cast<AIreneCharacter>(GetOwningPlayer()->GetPawn());
	if (Player != nullptr) Player->bInputStop = true;

	if (!dialogueArr.IsValidIndex(dialogueIndex))
	{
		if (Owner != nullptr)
			Owner->PlaySeq.Broadcast();

		RemoveFromParent();
		RemoveFromViewport();

		if (Player != nullptr) Player->bInputStop = false;

		return;
	}

	if (DialgoueScroll->GetChildrenCount() >= 1)
	{
		auto ChildPanel = Cast<UDialogChildWidget_D>(DialgoueScroll->GetChildAt(DialgoueScroll->GetChildrenCount() - 1));
		if (ChildPanel->IsHandleActive()) return;
	}

	auto findNextDialogue = dialogueTable->FindRow<FScriptData>(dialogueArr[dialogueIndex], "");
	if (findNextDialogue == nullptr) return;

	auto ChildWidget = CreateWidget<UDialogChildWidget_D>(GetWorld(), ChildWidget_C);
	ChildWidget->DefaultSetting(this, findNextDialogue->String);

	if (DialgoueScroll->GetChildrenCount() >= 5) DialgoueScroll->RemoveChildAt(0);
	auto beforeDialogue = Cast<UDialogChildWidget_D>(DialgoueScroll->GetChildAt(DialgoueScroll->GetChildrenCount() - 1));
	if (beforeDialogue != nullptr) beforeDialogue->tryDiableDialgoue();

	DialgoueScroll->AddChild(ChildWidget);
	DialgoueScroll->ScrollToEnd();

	if (findNextDialogue->Name.ToString() == TEXT("아이린")) ChildWidget->SetTalkPerson(false);
	else ChildWidget->SetTalkPerson(true);

	if (findNextDialogue->Name.ToString() != lastTalkingPerson.ToString())
	{
		if (findNextDialogue->Name.ToString() == TEXT("아이린"))
		{
			PlayAnimation(widgetAnimArr[3]);
			PlayAnimationReverse(widgetAnimArr[2]);
		}
		else
		{
			PlayAnimation(widgetAnimArr[2]);
			PlayAnimationReverse(widgetAnimArr[3]);
		}
	}
	lastTalkingPerson = findNextDialogue->Name;
	
	ChildWidget->DialgoueStart();
	dialogueIndex++;
}

void UDialogHistoryWidget_D::trySkipDialogue()
{
	if (DialogueHistoryCanvas->GetVisibility() == ESlateVisibility::Collapsed)
	{
		auto AutoIrene = Cast<AIreneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		AutoIrene->IreneUIManager->PlayerHud->ActionWidgetOff();

		DialogueHistoryCanvas->SetVisibility(ESlateVisibility::Visible);
		DialogueHistoryCanvas->SetRenderOpacity(1.0f);
		nextTalk();
		return;
	}

	if (DialgoueScroll->GetChildrenCount() >= 1)
	{
		auto ChildPanel = Cast<UDialogChildWidget_D>(DialgoueScroll->GetChildAt(DialgoueScroll->GetChildrenCount() - 1));
		if (ChildPanel != nullptr)
		{
			if (ChildPanel->IsHandleActive())
				ChildPanel->SkipDialogue();
			else
				nextTalk();
		}
	}
}
