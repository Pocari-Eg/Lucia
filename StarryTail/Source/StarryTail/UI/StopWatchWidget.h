// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Blueprint/UserWidget.h"
#include "StopWatchWidget.generated.h"

/**
 *
 */
UCLASS()
class STARRYTAIL_API UStopWatchWidget : public UUserWidget
{
	GENERATED_BODY()
	public:

	UPROPERTY(BluePrintReadOnly)
	int32 TimerMinutes;
	UPROPERTY(BluePrintReadOnly)
	int32 TimerSeconds;

	UPROPERTY(BluePrintReadOnly)
	WatchState CurrentState;
};
