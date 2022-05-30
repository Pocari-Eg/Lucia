// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "KeySetWidget.h"
#include"SoundSettingWidget.h"
#include "Components/Button.h"
#include "Components/InputKeySelector.h"


void UPauseWidget::WidgetOn()
{
 
    bIsEnableResume = true;
    SetVisibility(ESlateVisibility::Visible);
    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
    GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

bool UPauseWidget::WidgetOff()
{
    if (bIsEnableResume == true) {
        UGameplayStatics::SetGamePaused(GetWorld(), false);
        SetVisibility(ESlateVisibility::Hidden);
        GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
        GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
        return true;
    }
    else {
        return false;
    }
  
}


void UPauseWidget::KeySetWidgetOn()
{
    EnableButton();
    SoundSetWidget->SetVisibility(ESlateVisibility::Hidden);
    KeySetWidget->SetVisibility(ESlateVisibility::Visible);
  
    
}

void UPauseWidget::SoundSetWidgetOn()
{
    EnableButton();
    KeySetWidget->SetVisibility(ESlateVisibility::Hidden);
    SoundSetWidget->SetVisibility(ESlateVisibility::Visible);
}

void UPauseWidget::DisableButton()
{
    bIsEnableResume = false;
    ResumButton->SetIsEnabled(false);
    SoundWidgetButton->SetIsEnabled(false);
    QuitButton->SetIsEnabled(false);
}

void UPauseWidget::EnableButton()
{
    bIsEnableResume = true;
    ResumButton->SetIsEnabled(true);
    SoundWidgetButton->SetIsEnabled(true);
    QuitButton->SetIsEnabled(true);
}

void UPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    KeySetWidget = Cast<UKeySetWidget>(GetWidgetFromName(TEXT("BP_KeysettingWidget")));
    SoundSetWidget = Cast<USoundSettingWidget>(GetWidgetFromName(TEXT("BP_SoundSettingWidget")));

   ResumButton = Cast<UButton>(GetWidgetFromName(TEXT("Resume")));
   SoundWidgetButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundSetting")));
   QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("Quit")));

    KeySetWidget->SetVisibility(ESlateVisibility::Hidden);
    SoundSetWidget->SetVisibility(ESlateVisibility::Hidden);


    KeySetWidget->BindPauseWidget(this);
    SoundSetWidget->BindPauseWidget(this);
}




