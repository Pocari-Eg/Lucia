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
	

	//위젯에 표시할 분
	UPROPERTY(BluePrintReadOnly)
	int32 TimerMinutes;
	//위젯에 표시할 초
	UPROPERTY(BluePrintReadOnly)
	int32 TimerSeconds;

	//위젯에 표시할 현재 상태
	UPROPERTY(BluePrintReadOnly)
	WatchState CurrentState;
};
