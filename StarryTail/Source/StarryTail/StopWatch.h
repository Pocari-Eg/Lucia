// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StarryTail.h"
#include "GameFramework/Actor.h"
#include"UI/StopWatchWidget.h"


#include "StopWatch.generated.h"


UCLASS()
class STARRYTAIL_API AStopWatch : public AActor
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TIMER)
	int Minutes; // 분
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TIMER)
	int Seconds; // 초

	WatchState CurrentState; // 현재 스탑워치 상태
protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UStopWatchWidget> TimerWidgetClass;   //스탑워치 위젯 클래스 
private:

	FTimerHandle TimerHandle; // TimerHandle;

	UPROPERTY()
	class UStopWatchWidget* TimerWidget; //스탑워치 위젯	

public:
	// Sets default values for this actor's properties
	AStopWatch();

	void InitStopWatch(); //스탑워치 초기화
	void WatchControl();  // 스탑워치 조작
	void WatchReset(); // 스탑워치 리셋
protected:

private:
	void WatchPlay();  // 스탑워치 재생 

};
