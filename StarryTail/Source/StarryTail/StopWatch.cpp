// Fill out your copyright notice in the Description page of Project Settings.


#include "StopWatch.h"

#include "UI/StopWatchWidget.h"
// Sets default values
AStopWatch::AStopWatch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FClassFinder<UStopWatchWidget>UI_TIMERWIDGET_C(TEXT("/Game/Developers/Pocari/Collections/Widget/BP_StopWatchWidget.BP_StopWatchWidget_C"));
	if (UI_TIMERWIDGET_C.Succeeded())
	{
		TimerWidgetClass = UI_TIMERWIDGET_C.Class;
	}
}

void AStopWatch::InitStopWatch() //위젯 생성 및 스탑워치 리셋
{

	TimerWidget = CreateWidget<UStopWatchWidget>(GetGameInstance(), TimerWidgetClass);
	TimerWidget->AddToViewport();

	CurrentState = WatchState::e_Reset;
	TimerWidget->CurrentState = CurrentState;
	Minutes = 0;
	Seconds = 0;
	TimerWidget->TimerMinutes = Minutes;
	TimerWidget->TimerSeconds = Seconds;
}

void AStopWatch::WatchControl() //스탑워치 조작
{
	switch (CurrentState)
	{
	case WatchState::e_Reset:
		CurrentState = WatchState::e_Play;
		TimerWidget->CurrentState = CurrentState;

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AStopWatch::WatchPlay, 1.0f, true, 0.0f);
		break;
	case WatchState::e_Play:
		CurrentState = WatchState::e_Pause;
		TimerWidget->CurrentState = CurrentState;
		GetWorldTimerManager().ClearTimer(TimerHandle);
		break;
	case WatchState::e_Pause:
		CurrentState = WatchState::e_Play;
		TimerWidget->CurrentState = CurrentState;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AStopWatch::WatchPlay, 1.0f, true, 0.0f);
		break;
	default:
		break;
	}
}

void AStopWatch::WatchReset() //스탑워치 리셋
{
	//스탑워치가 pause 상태일때만 초기화가 가능
	if (CurrentState == WatchState::e_Pause) {
		CurrentState = WatchState::e_Reset;
		TimerWidget->CurrentState = CurrentState;
		Minutes = 0;
		Seconds = 0;
		TimerWidget->TimerMinutes = Minutes;
		TimerWidget->TimerSeconds = Seconds;
	}
}

void AStopWatch::WatchPlay() //스탑워치 시작
{
	if (Seconds != 59)
	{
		Seconds += 1;
	}
	else {
		Minutes += 1;
		Seconds = 0;
	}
	TimerWidget->TimerMinutes = Minutes;
	TimerWidget->TimerSeconds = Seconds;
}

// Called when the game starts or when spawned
