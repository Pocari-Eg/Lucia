// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "KeySetWidget.h"
#include"SoundSettingWidget.h"
#include "Components/InputKeySelector.h"


void UPauseWidget::WidgetOn()
{
 
    SetVisibility(ESlateVisibility::Visible);
    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());
    GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

bool UPauseWidget::WidgetOff()
{
    if (IsSoundSetwidgetOn == false && IsKeySetWidgetOn == false) {
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
    IsKeySetWidgetOn = true;
    KeySetWidget->WidgetOn(this);
  
    
}

void UPauseWidget::SoundSetWidgetOn()
{
    IsSoundSetwidgetOn = true;
    SoundSetWidget->WidgetOn(this);
}

void UPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    KeySetWidget = Cast<UKeySetWidget>(GetWidgetFromName(TEXT("BP_KeysettingWidget")));
    SoundSetWidget = Cast<USoundSettingWidget>(GetWidgetFromName(TEXT("BP_SoundSettingWidget")));

    KeySetWidget->SetVisibility(ESlateVisibility::Hidden);
    SoundSetWidget->SetVisibility(ESlateVisibility::Hidden);

}




