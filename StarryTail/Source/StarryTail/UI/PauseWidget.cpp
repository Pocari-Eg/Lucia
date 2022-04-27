// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Kismet/GameplayStatics.h"
#include "KeySetWidget.h"
#include "Components/InputKeySelector.h"


void UPauseWidget::WidgetOn()
{
 
    AddToViewport();
    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
    GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UPauseWidget::WidgetOff()
{

    RemoveFromViewport();
    GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameOnly());
    GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
    UGameplayStatics::SetGamePaused(GetWorld(), false);
  
}

void UPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();
    UE_LOG(LogTemp, Error, TEXT("Init UMG"));

   // widget
    KeySetWidgetClass = LoadClass<UKeySetWidget>(NULL, TEXT("/Game/UI/BluePrint/BP_KeysettingWidget.BP_KeysettingWidget_C"), NULL, LOAD_None, NULL);
    

    if (KeySetWidgetClass !=nullptr)
    {
        KeySetWidget = CreateWidget<UKeySetWidget>(GetWorld(), KeySetWidgetClass);
        KeySetWidget->AddToViewport();
        KeySetWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UPauseWidget::KeySetWidgetOn()
{
    KeySetWidget->WidgetOn(this);
    
}




