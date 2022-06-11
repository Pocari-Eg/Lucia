// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BluePrintReadWrite,Category="TUTORIAL")
	FString TutorialNum;


public:
	UFUNCTION(BlueprintImplementableEvent)
	void  		OnAnimationEvent();

	void PlayTutorial(FString Num);
};
