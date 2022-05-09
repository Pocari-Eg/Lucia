// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"


void UDialogWidget::SetDialog(FString dialog)
{
	SetVisibility(ESlateVisibility::Visible);
	//메시지를 담아온다
	InputDialog = dialog;
	Length = 0;
	CurrentTextKeeptime = TextKeepTime;
	SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UDialogWidget::PlayDialog, TextPrintTime, true, 0.0f);
}

void UDialogWidget::PlayDialog()
{

	//현재 출력된 메시지가 전부 출력되면
	 if (InputDialog.Len()+2 <= Length)
	{
		 if (CurrentTextKeeptime > 0.0f)
		 {
			 CurrentTextKeeptime -= TextPrintTime;
		
		 }
		 else {
			 CurrentTextKeeptime = TextKeepTime;
			 OutputDialog = "";
			 SetVisibility(ESlateVisibility::Hidden);
			 //타이머 초기화로 
			 GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
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
	SetVisibility(ESlateVisibility::Hidden);
}

