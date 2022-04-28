// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySetWidget.h"
#include "GameFramework/InputSettings.h"
#include "Components/InputKeySelector.h"
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
	
}


void UKeySetWidget::UpdateKeyName(UPARAM(ref)TArray<UInputKeySelector*>& InputKey)
{
	UE_LOG(LogTemp, Error, TEXT("IN_FUNC"));

	auto CurrentAction = UInputSettings::GetInputSettings()->GetActionMappings();

		CurrentAction.Sort([](const FInputActionKeyMapping& A, const FInputActionKeyMapping& B) {
			return A.ActionName.ToString().Len() < B.ActionName.ToString().Len();
			});

		InputKey.Sort([](const UInputKeySelector& A, const UInputKeySelector& B) {
			return A.GetName().Len() < B.GetName().Len();
			});

	int num = InputKey.Num();
	int index;
	IsEmptyKey = false;
	IsUpdatekey = true;
	for (int i = 0; i < num; i++)
	{
		
		FInputChord Update(CurrentAction[i].Key, CurrentAction[i].bShift, CurrentAction[i].bCtrl, CurrentAction[i].bAlt, CurrentAction[i].bCmd);



		if (Update.Key == NONE)
		{
			IsEmptyKey = true;
		}
		for (int j = 0; j < num; j++)
		{
			if (InputKey[j]->GetName() == CurrentAction[i].ActionName.ToString())
				index = j;
		}
		InputKey[index]->SetSelectedKey(Update);

		UE_LOG(LogTemp, Error, TEXT("IN_For1"));
	}
   
	IsUpdatekey = false;
}





