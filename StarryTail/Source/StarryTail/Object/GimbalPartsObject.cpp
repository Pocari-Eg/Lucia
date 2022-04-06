// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalPartsObject.h"


// Sets default values
AGimbalPartsObject::AGimbalPartsObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GIMBAL"));
	RootComponent = Gimbal;
	
	Gimbal->SetCollisionProfileName("NoCollision");

	IsGimbalOn = false;
	IsTimeLineOn = false;
	RotationAccel = 0.0f;

	
}

// Called when the game starts or when spawned
void AGimbalPartsObject::BeginPlay()
{
	Super::BeginPlay();
	
	//점령 델리게이트 설정
	 

	//타임라인 속도 설정
	GimbalTimeline.SetPlayRate(AccelSpeed);

	//타임라인 시작 호출 함수
	FOnTimelineFloat TimelineCallback;
	//타임라인 종료 호출 함수
	FOnTimelineEventStatic TimelineFinishedCallback;
	//함수 바인딩 
	TimelineCallback.BindUFunction(this, FName("Acceleration"));
	TimelineFinishedCallback.BindUFunction(this, FName(TEXT("AccelerationOff")));
	GimbalTimeline.AddInterpFloat(TimeLineCurve, TimelineCallback);
	GimbalTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	GimbalTimeline.SetTimelineLength(1.0f);
}

// Called every frame
void AGimbalPartsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//타임라인 상태 설정
	if (IsTimeLineOn == true)GimbalTimeline.TickTimeline(DeltaTime);
	////현재 속성 짐벌이 켜지면 짐벌 회전
	//IsGimbalOn == true ? Gimbal->AddLocalRotation(FRotator(0.0f, GimbalSpeed * RotationAccel, 0.0f)) : Gimbal->AddLocalRotation(FRotator(0.0f, 0.0f, 0.0f));\

	if (IsGimbalOn)
	{
		switch (Attributes)
		{
		case EAttributeKeyword::e_Fire:
			Gimbal->AddWorldRotation(FRotator(0.0f, GimbalSpeed * RotationAccel, 0.0f));
			break;
		case EAttributeKeyword::e_Water:
			Gimbal->AddWorldRotation(FRotator(0.0f, 0.0f, GimbalSpeed * RotationAccel));
			break;
		case EAttributeKeyword::e_Thunder:
			Gimbal->AddWorldRotation(FRotator(GimbalSpeed * RotationAccel, 0.0f, 0.0f));
			break;
		default:
			break;
		}
	}
	else {
		Gimbal->AddLocalRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AGimbalPartsObject::GimbalStart()
{
	IsGimbalOn = true;
	IsTimeLineOn = true;
	GimbalTimeline.PlayFromStart();
}

void AGimbalPartsObject::GimbalReverse()
{
	IsTimeLineOn = true;
	GimbalTimeline.Reverse();
}



void AGimbalPartsObject::Acceleration()
{
	//짐벌 회전 가속 
	float TimelineVal = GimbalTimeline.GetPlaybackPosition();
	RotationAccel = TimeLineCurve->GetFloatValue(TimelineVal);
}

void AGimbalPartsObject::AccelerationOff()
{
	//짐벌 회전 속도 고정
	IsTimeLineOn = false;
	if (RotationAccel == 0.0f)
	{
		if (IsGimbalOn) IsGimbalOn = false;

	}
}

