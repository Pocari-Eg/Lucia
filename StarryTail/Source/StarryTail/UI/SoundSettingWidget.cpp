// Fill out your copyright notice in the Description page of Project Settings.



#include "SoundSettingWidget.h"


void USoundSettingWidget::BindPauseWidget(UPauseWidget* CurrentWidget)
{
	PauseWidget = CurrentWidget;
}

void USoundSettingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BGMWidget.CheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("BGMCheckBox")));
	BGMWidget.Slider = Cast<USlider>(GetWidgetFromName(TEXT("BGMSlider")));

	SFXWidget.CheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("SFXCheckBox")));
	SFXWidget.Slider = Cast<USlider>(GetWidgetFromName(TEXT("SFXSlider")));

}

void USoundSettingWidget::SoundWidgetSet()
{
	auto Instnace = Cast<USTGameInstance>(GetGameInstance());
	
	if (Instnace != nullptr) {
		Instnace->GetSoundSetting()->BGM_Mute == false ? BGMWidget.CheckBox->SetCheckedState(ECheckBoxState::Unchecked) : BGMWidget.CheckBox->SetCheckedState(ECheckBoxState::Checked);
		Instnace->GetSoundSetting()->SFX_Mute == false ? SFXWidget.CheckBox->SetCheckedState(ECheckBoxState::Unchecked) : SFXWidget.CheckBox->SetCheckedState(ECheckBoxState::Checked);

	    BGMWidget.Slider->SetValue(Instnace->GetSoundSetting()->BGM_Volume);
		SFXWidget.Slider->SetValue(Instnace->GetSoundSetting()->SFX_Volume);
	}
}

void USoundSettingWidget::SoundSettingSave()
{

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr) {

		BGMWidget.CheckBox->GetCheckedState() == ECheckBoxState::Checked ? Instance->GetSoundSetting()->BGM_Mute = true : Instance->GetSoundSetting()->BGM_Mute = false;
		SFXWidget.CheckBox->GetCheckedState() == ECheckBoxState::Checked ? Instance->GetSoundSetting()->SFX_Mute = true : Instance->GetSoundSetting()->SFX_Mute = false;

		Instance->GetSoundSetting()->BGM_Volume = BGMWidget.Slider->GetValue();
		Instance->GetSoundSetting()->SFX_Volume = SFXWidget.Slider->GetValue();	
	}

}
