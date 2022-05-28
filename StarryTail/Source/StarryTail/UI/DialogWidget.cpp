﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"


void UDialogWidget::SetDialog(FScriptData* ScriptData)
{
	if (TextBox != nullptr)
	{
	
		FColor NewColor = FColor(ScriptData->R, ScriptData->G, ScriptData->B,255.0f);
		TextBox->SetColorAndOpacity(FSlateColor(NewColor));
		
		
		if (ScriptData->Style == 0)
		{
			TextBox->SetFont(FSlateFontInfo(Font, ScriptData->Size, FName("Bold"),FFontOutlineSettings::NoOutline));
		}
		else {
			TextBox->SetFont(FSlateFontInfo(Font, ScriptData->Size, FName("Regular"), FFontOutlineSettings::NoOutline));
		}

	}
	

	//메시지를 담아온다
	InputDialog = *ScriptData->String;
	Length = 0;
	SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogWidget::PlayDialog, TextPrintTime, true, 0.0f);
}

void UDialogWidget::SkipDialog()
{
	SetDialogState(EDialogState::e_Complete);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	OutputDialog = InputDialog;
}

EDialogState UDialogWidget::GetDialogState()
{
	return CurrnetState;
}

void UDialogWidget::SetDialogState(EDialogState NewState)
{
	CurrnetState = NewState;
}

void UDialogWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TextBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBox")));

	Font= LoadObject<UObject>(NULL, TEXT("/Engine/EngineFonts/Roboto.Roboto"), NULL, LOAD_None, NULL);

	CurrnetState = EDialogState::e_Disable;
	
}

void UDialogWidget::PlayDialog()
{

	//현재 출력된 메시지가 전부 출력되면
	 if (InputDialog.Len()+2 <= Length)
	  {
		 SetDialogState(EDialogState::e_Complete);
		 GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	  } 
	 else 	if (InputDialog.Len() + 2 > Length)
	{
		for (int i = 0; i < Length; i++)
		{
			//Ouptdialog에 있는 문자열이 UI에 표시되므로 Inputdialog에서 한글자씩 받아옴
			OutputDialog = *InputDialog.Mid(0, i);
		}
		Length++;
	}
	
}
void UDialogWidget::EndDialog()
{
	OutputDialog = "";
	SetVisibility(ESlateVisibility::Hidden);
}

