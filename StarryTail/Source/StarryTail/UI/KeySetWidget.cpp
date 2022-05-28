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
	PauseWidget->IsKeySetWidgetOn = false;
	this->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->SetVisibility(ESlateVisibility::Visible);
}

void UKeySetWidget::ChangeActionKey(const FName ActionName,  UPARAM(ref)FInputChord& InputKey)
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
	

		UpdateActionKeyName();
		SetExitEnable();
}


void UKeySetWidget::ChangeAxisKey(const FName AxisName, UPARAM(ref)FInputChord& InputKey)
{
	TArray< FInputAxisKeyMapping> CurrentAxisMapping = UInputSettings::GetInputSettings()->GetAxisMappings();
	FName SameKeyName;

	for (int i = 0; i < CurrentAxisMapping.Num(); i++)
	{
		FInputChord currentkey(CurrentAxisMapping[i].Key);

		if (InputKey == currentkey)
		{
			SameKeyName = CurrentAxisMapping[i].AxisName;
			TArray<FInputAxisKeyMapping> Refresh;
			UInputSettings::GetInputSettings()->GetAxisMappingByName(SameKeyName, Refresh);
			UInputSettings::GetInputSettings()->RemoveAxisMapping(Refresh[0], false);
			FInputAxisKeyMapping Rfreshkey(SameKeyName);
			UInputSettings::GetInputSettings()->AddAxisMapping(Rfreshkey, false);


		}
		else {

		}
	}

	TArray<FInputAxisKeyMapping> OutMap;
	UInputSettings::GetInputSettings()->GetAxisMappingByName(AxisName, OutMap);
	UInputSettings::GetInputSettings()->RemoveAxisMapping(OutMap[0], false);
	FInputAxisKeyMapping Newkey(AxisName, InputKey.Key);
	UInputSettings::GetInputSettings()->AddAxisMapping(Newkey, true);


	UpdateAxisKeyName();
	SetExitEnable();
}

void UKeySetWidget::UpdateActionKeyName()
{
	auto CurrentAction = UInputSettings::GetInputSettings()->GetActionMappings();

	int InputkeyNum = InputActionKeyArray.Num();
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
			if (InputActionKeyArray[j]->GetName() == CurrentAction[i].ActionName.ToString())
			{
				InputActionKeyArray[j]->SetSelectedKey(Update);
				break;
			}
		}
		
	}
   
	IsUpdatekey = false;
}

void UKeySetWidget::UpdateAxisKeyName()
{
	auto CurrentAxis = UInputSettings::GetInputSettings()->GetAxisMappings();

	int InputkeyNum = InputAxisKeyArray.Num();
	int CurrentKeyNum = CurrentAxis.Num();
	IsEmptyKey = false;
	IsUpdatekey = true;
	for (int i = 0; i < CurrentKeyNum; i++)
	{

		FInputChord Update(CurrentAxis[i].Key);

		if (Update.Key == NONE)
		{
			IsEmptyKey = true;
			STARRYLOG_S(Error);
		}
		for (int j = 0; j < InputkeyNum; j++)
		{
			if (InputAxisKeyArray[j]->GetName() == CurrentAxis[i].AxisName.ToString())
			{
				InputAxisKeyArray[j]->SetSelectedKey(Update);
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





