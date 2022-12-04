// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "../STGameInstance.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto Instnace = Cast<USTGameInstance>(GetGameInstance());
	if (Instnace != nullptr)
	{
		if (!Instnace->GetIsPlaying())
		{
			tryPlay(EPlayTutorial::Move);
		}
	}

}

void UTutorialWidget::PlayTutorial(FString Num)
{
	TutorialNum = Num;
	OnAnimationEvent();
}

void UTutorialWidget::trystopPlay(EPlayTutorial __play)
{
	Pstopdelegate.Broadcast(__play);
}

void UTutorialWidget::tryTutoInfo(EPlayTuto __play)
{
	Pinfodelegate.Broadcast(__play);
}

void UTutorialWidget::tryPlay(EPlayTutorial __play)
{
	Pdelegate.Broadcast(__play);
}
