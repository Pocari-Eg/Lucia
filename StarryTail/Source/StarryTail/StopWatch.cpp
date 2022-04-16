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

void AStopWatch::InitStopWatch() //���� ���� �� ��ž��ġ ����
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

void AStopWatch::WatchControl() //��ž��ġ ����
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

void AStopWatch::WatchReset() //��ž��ġ ����
{
	//��ž��ġ�� pause �����϶��� �ʱ�ȭ�� ����
	if (CurrentState == WatchState::e_Pause) {
		CurrentState = WatchState::e_Reset;
		TimerWidget->CurrentState = CurrentState;
		Minutes = 0;
		Seconds = 0;
		TimerWidget->TimerMinutes = Minutes;
		TimerWidget->TimerSeconds = Seconds;
	}
}

void AStopWatch::WatchPlay() //��ž��ġ ����
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
