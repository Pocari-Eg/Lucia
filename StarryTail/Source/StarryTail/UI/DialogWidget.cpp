// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"
#include "Components/Image.h"
#include "PlayerHudWidget.h"

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
	
	if (ScriptData->Condition == 1) {

		//메시지를 담아온다
		InputDialog = *ScriptData->String;
		Length = 0;
		SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogWidget::PlayDialog, TextPrintTime, true, 0.0f);
	}
	else if(ScriptData->Condition == 0)
	{
		//메시지를 담아온다
		InputDialog = *ScriptData->String;
		Length = 0;
		SetVisibility(ESlateVisibility::Visible);
		CurrentTextKeeptime = TextKeepTime;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogWidget::PlayPopUpDialog, TextPrintTime, true, 0.0f);

	}

	if (NextArrow != nullptr)
		NextArrow->SetVisibility(ESlateVisibility::Hidden);

}

void UDialogWidget::SkipDialog()
{
	SetDialogState(EDialogState::e_Complete);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	OutputDialog = InputDialog;
	if (NextArrow != nullptr)
		NextArrow->SetVisibility(ESlateVisibility::Visible);
}

EDialogState UDialogWidget::GetDialogState()
{
	return CurrnetState;
}

void UDialogWidget::SetDialogState(EDialogState NewState)
{
	CurrnetState = NewState;
}

void UDialogWidget::BindPlayerHud(class UPlayerHudWidget* NewPlayerHud)
{
	PlayerHud = NewPlayerHud;
}

void UDialogWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	TextBox = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBox")));

	Font= LoadObject<UObject>(NULL, TEXT("/Engine/EngineFonts/Roboto.Roboto"), NULL, LOAD_None, NULL);

	CurrnetState = EDialogState::e_Disable;
	NextArrow= Cast<UImage>(GetWidgetFromName(TEXT("NextArrow")));
}

void UDialogWidget::PlayDialog()
{

	//현재 출력된 메시지가 전부 출력되면
	 if (InputDialog.Len()+2 <= Length)
	  {
		 SetDialogState(EDialogState::e_Complete);
		 if(NextArrow!=nullptr)
		 NextArrow->SetVisibility(ESlateVisibility::Visible);
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
void UDialogWidget::PlayPopUpDialog()
{
	//현재 출력된 메시지가 전부 출력되면
	if (InputDialog.Len() + 2 <= Length)
	{
		if (CurrentTextKeeptime > 0.0f)
		{
			CurrentTextKeeptime -= TextPrintTime;
		
		}
		else {
			CurrentTextKeeptime = TextKeepTime;
			//타이머 초기화로 
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
			if (PlayerHud->ContinueDialog())
			{
				PlayerHud->PlayPopUp();
			}
			else {
				PlayerHud->ExitPopUp();
			}
		}

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

