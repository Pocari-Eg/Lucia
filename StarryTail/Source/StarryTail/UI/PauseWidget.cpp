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

void UPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Error, TEXT("Init UMG"));

   //KeySet widget
    KeySetWidgetClass = LoadClass<UKeySetWidget>(NULL, TEXT("/Game/UI/BluePrint/Setting/BP_KeysettingWidget.BP_KeysettingWidget_C"), NULL, LOAD_None, NULL);
    

    if (KeySetWidgetClass !=nullptr)
    {
        KeySetWidget = CreateWidget<UKeySetWidget>(GetWorld(), KeySetWidgetClass);
        KeySetWidget->AddToViewport();
        KeySetWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    // widget
    SoundSetWidgetClass = LoadClass<USoundSettingWidget>(NULL, TEXT("/Game/UI/BluePrint/Setting/BP_SoundSettingWidget.BP_SoundSettingWidget_C"), NULL, LOAD_None, NULL);


    if (SoundSetWidgetClass != nullptr)
    {
        SoundSetWidget = CreateWidget<USoundSettingWidget>(GetWorld(), SoundSetWidgetClass);
        SoundSetWidget->AddToViewport();
        SoundSetWidget->SetVisibility(ESlateVisibility::Hidden);
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




