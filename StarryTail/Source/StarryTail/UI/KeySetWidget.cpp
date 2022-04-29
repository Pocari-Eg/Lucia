// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySetWidget.h"
#include "GameFramework/InputSettings.h"
#include "Components/Button.h"
#include "Kismet/KismetInputLibrary.h"
void UKeySetWidget::WidgetOn(UPauseWidget* widget)
{
	PauseWidget = widget;
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	this->SetVisibility(ESlateVisibility::Visible);
	IsEmptyKey = false;
}

void UKeySetWidget::WidgetOff()
{
	this->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
}

void UKeySetWidget::ChangeKey(const FName ActionName,  UPARAM(ref)FInputChord& InputKey)
{
		TArray< FInputActionKeyMapping> CurrentActionMapping = UInputSettings::GetInputSettings()->GetActionMappings();
		FName SameKeyName;

		for (int i = 0; i < CurrentActionMapping.Num(); i++)
		{
			FInputChord currentkey(CurrentActionMapping[i].Key, CurrentActionMapping[i].bShift, CurrentActionMapping[i].bCtrl, CurrentActionMapping[i].bAlt, CurrentActionMapping[i].bCmd);

			if (InputKey == currentkey)
			{
				SameKeyName = CurrentActionMapping[i].ActionName;
				TArray<FInputActionKeyMapping> Refresh;
				UInputSettings::GetInputSettings()->GetActionMappingByName(SameKeyName, Refresh);
				UInputSettings::GetInputSettings()->RemoveActionMapping(Refresh[0], false);
				FInputActionKeyMapping Rfreshkey(SameKeyName, NONE, false, false, false, false);
				UInputSettings::GetInputSettings()->AddActionMapping(Rfreshkey, false);


			}
			else {

			}
		}

		TArray<FInputActionKeyMapping> OutMap;
		UInputSettings::GetInputSettings()->GetActionMappingByName(ActionName, OutMap);
		UInputSettings::GetInputSettings()->RemoveActionMapping(OutMap[0], false);
		FInputActionKeyMapping Newkey(ActionName, InputKey.Key, InputKey.bShift, InputKey.bCtrl, InputKey.bAlt, InputKey.bCmd);
		UInputSettings::GetInputSettings()->AddActionMapping(Newkey, true);
	

		UpdateKeyName();
		SetExitEnable();
}


void UKeySetWidget::UpdateKeyName()
{
	auto CurrentAction = UInputSettings::GetInputSettings()->GetActionMappings();

	int InputkeyNum = InputKeyArray.Num();
	int CurrentKeyNum = CurrentAction.Num();
	IsEmptyKey = false;
	IsUpdatekey = true;
	for (int i = 0; i < CurrentKeyNum; i++)
	{
		
		FInputChord Update(CurrentAction[i].Key, CurrentAction[i].bShift, CurrentAction[i].bCtrl, CurrentAction[i].bAlt, CurrentAction[i].bCmd);

		if (Update.Key == NONE)
		{
			IsEmptyKey = true;
		}
		for (int j = 0; j < InputkeyNum; j++)
		{
			if (InputKeyArray[j]->GetName() == CurrentAction[i].ActionName.ToString())
			{
				InputKeyArray[j]->SetSelectedKey(Update);
				break;
			}
		}
		
	}
   
	IsUpdatekey = false;
}

void UKeySetWidget::SetExitEnable()
{
	IsEmptyKey == true ? ExitButton->SetIsEnabled(false) : ExitButton->SetIsEnabled(true);
}

void UKeySetWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("Exit")));
}





