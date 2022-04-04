// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalObject.h"

// Sets default values
AGimbalObject::AGimbalObject()
{
	//초기 세팅
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	RootComponent = Center;
	
	
	FireGimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FIREGIMBAL"));
	WaterGimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATERGIMBAL"));
	ThunderGimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("THUNDERGIMBAL"));

	FireGimbal->SetupAttachment(RootComponent);
	WaterGimbal->SetupAttachment(RootComponent);
	ThunderGimbal->SetupAttachment(RootComponent);

	FireGimbal->SetRelativeLocation(FVector::ZeroVector);
	WaterGimbal->SetRelativeLocation(FVector::ZeroVector);
	ThunderGimbal->SetRelativeLocation(FVector::ZeroVector);

	FireGimbal->SetCollisionProfileName("NoCollision");
	WaterGimbal->SetCollisionProfileName("NoCollision");
	ThunderGimbal->SetCollisionProfileName("NoCollision");

	IsFireGimbalOn = false;
	IsWaterGimbalOn = false;
	IsThunderGimbalOn = false;

	IsAllGimbalOn = false;


	MaxAttributesGauge = 100.0f;
	CurrentAttributesGauge = 0.0f;
	AttributesGaugeNum = 10.0f;

	static ConstructorHelpers::FObjectFinder<UCurveFloat>CURVE(TEXT("/Game/Developers/Pocari/Collections/Curve/PartsObjCurve.PartsObjCurve"));

	if (CURVE.Succeeded())
	{
		TimeLineCurve = CURVE.Object;
	}

	IsTimeLineOn = false;

	RotationAccel = 0.0f;
	AccelSpeed = 0.1f;
}

// Called when the game starts or when spawned
void AGimbalObject::BeginPlay()
{
	Super::BeginPlay();
	
	//점령 델리게이트 설정
	if(FireOccupiedArea!=nullptr)
		FireOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::FireGimbalOnOff);
	if (WaterOccupiedArea != nullptr)
		WaterOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::WaterGimbalOnOff);
	if (ThungerOccupiedArea != nullptr)
		ThungerOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::ThunderGimbalOnOff);
	

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
void AGimbalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//타임라인 상태 설정
	if (IsTimeLineOn == true)GimbalTimeline.TickTimeline(DeltaTime);

	//현재 속성 짐벌이 켜지면 짐벌 회전
	IsFireGimbalOn == true ? FireGimbal->AddWorldRotation(FRotator(0.0f, FireGimbalSpeed* RotationAccel, 0.0f)) : FireGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	IsWaterGimbalOn == true ? WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, WaterGimbalSpeed* RotationAccel)) : WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	IsThunderGimbalOn == true ? ThunderGimbal->AddWorldRotation(FRotator(ThunderGimbalSpeed* RotationAccel, 0.0f, 0.0f)) : ThunderGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));

}

void AGimbalObject::Acceleration()
{

	//짐벌 회전 가속 
	float TimelineVal = GimbalTimeline.GetPlaybackPosition();
	 RotationAccel = TimeLineCurve->GetFloatValue(TimelineVal);

   
}

void AGimbalObject::AccelerationOff()
{
	//짐벌 회전 속도 고정
	IsTimeLineOn = false;
	if (RotationAccel == 0.0f)
	{
		if (IsFireGimbalOn) IsFireGimbalOn = false;
		else if (IsWaterGimbalOn) IsWaterGimbalOn = false;
		else if (IsThunderGimbalOn) IsThunderGimbalOn = false;

	}
}

void AGimbalObject::GimbalGaugeOn()
{
	//목표 수치에 도착하면 상승 종료
	if (CurrentAttributesGauge >= MaxAttributesGauge) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	//도달 못하면 수치 상승
	else if (CurrentAttributesGauge <= MaxAttributesGauge - AttributesGaugeNum)
	{
		CurrentAttributesGauge += AttributesGaugeNum;
	}
}

void AGimbalObject::FireGimbalOnOff()
{
	//짐벌이 꺼저있으면 
	if (IsFireGimbalOn == false) {
		//짐벌을 키고 회전 속도 가속
		IsFireGimbalOn = true;
		IsTimeLineOn = true;
		GimbalTimeline.PlayFromStart();
		if (IsWaterGimbalOn == true && IsThunderGimbalOn == true)
		{
			//다른 짐벌도 켜있으면 원소 게이지 상승
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		//짐벌 종료
		//회전 속도 감속
		IsAllGimbalOn = false;
		IsTimeLineOn = true;
		GimbalTimeline.Reverse();
		//원소 게이지 상승 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

//이하동문
void AGimbalObject::WaterGimbalOnOff()
{
	if (IsWaterGimbalOn == false) {
		IsTimeLineOn = true;
		IsWaterGimbalOn = true;
		GimbalTimeline.PlayFromStart();
		if (IsFireGimbalOn == true && IsThunderGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;
		IsTimeLineOn = true;
		GimbalTimeline.Reverse();
		GetWorldTimerManager().ClearTimer(TimerHandle);

	}
}

void AGimbalObject::ThunderGimbalOnOff()
{
	if (IsThunderGimbalOn == false) {
		IsThunderGimbalOn = true;
		IsTimeLineOn = true;

		GimbalTimeline.PlayFromStart();
		if (IsWaterGimbalOn == true && IsFireGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;
		IsTimeLineOn = true;
		GimbalTimeline.Reverse();
		GetWorldTimerManager().ClearTimer(TimerHandle);

	}
}




