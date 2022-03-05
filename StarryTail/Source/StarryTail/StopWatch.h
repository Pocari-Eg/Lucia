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
	int Minutes; // ��
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TIMER)
	int Seconds; // ��

	WatchState CurrentState; // ���� ��ž��ġ ����
protected:

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = UI)
	TSubclassOf<class UStopWatchWidget> TimerWidgetClass;   //��ž��ġ ���� Ŭ���� 
private:

	FTimerHandle TimerHandle; // TimerHandle;

	UPROPERTY()
	class UStopWatchWidget* TimerWidget; //��ž��ġ ����	

public:
	// Sets default values for this actor's properties
	AStopWatch();

	void InitStopWatch(); //��ž��ġ �ʱ�ȭ
	void WatchControl();  // ��ž��ġ ����
	void WatchReset(); // ��ž��ġ ����
protected:

private:
	void WatchPlay();  // ��ž��ġ ��� 

};
