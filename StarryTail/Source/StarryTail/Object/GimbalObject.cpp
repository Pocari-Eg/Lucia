// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalObject.h"

// Sets default values
AGimbalObject::AGimbalObject()
{
	//초기 세팅
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	
	RootComponent = Center;

	ChildFireGimbal = CreateDefaultSubobject<UChildActorComponent>(TEXT("FIREGIMBAL"));
	ChildWaterGimbal = CreateDefaultSubobject<UChildActorComponent>(TEXT("WATERGIMBAL"));
	ChildThunderGimbal = CreateDefaultSubobject<UChildActorComponent>(TEXT("THUNDERGIMBAL"));

	ChildFireGimbal->SetChildActorClass(AGimbalPartsObject::StaticClass());
	ChildWaterGimbal->SetChildActorClass(AGimbalPartsObject::StaticClass());
	ChildThunderGimbal->SetChildActorClass(AGimbalPartsObject::StaticClass());

	ChildFireGimbal->SetupAttachment(RootComponent);
	ChildWaterGimbal->SetupAttachment(RootComponent);
	ChildThunderGimbal->SetupAttachment(RootComponent);

	ChildFireGimbal->SetRelativeLocation(FVector::ZeroVector);
	ChildWaterGimbal->SetRelativeLocation(FVector::ZeroVector);
	ChildThunderGimbal->SetRelativeLocation(FVector::ZeroVector);

	static ConstructorHelpers::FObjectFinder<UCurveFloat>CURVE(TEXT("/Game/Developers/Pocari/Collections/Curve/GimbalObjCurve.GimbalObjCurve"));
	if (CURVE.Succeeded())
	{
		TimeLineCurve = CURVE.Object;
	}

	MaxAttributesGauge = 100.0f;
	CurrentAttributesGauge = 0.0f;
	AttributesGaugeNum = 10.0f;
	IsAllGimbalOn = false;
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


}

void AGimbalObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FireGimbal = Cast<AGimbalPartsObject>(ChildFireGimbal->GetChildActor());
	FireGimbal->Gimbal->SetStaticMesh(FireGimbalMesh);
	FireGimbal->GimbalSpeed = FireGimbalSpeed;
	FireGimbal->AccelSpeed = AccelSpeed;
	FireGimbal->TimeLineCurve = TimeLineCurve;
	FireGimbal->Attributes = EAttributeKeyword::e_Fire;

	WaterGimbal = Cast<AGimbalPartsObject>(ChildWaterGimbal->GetChildActor());
	WaterGimbal->Gimbal->SetStaticMesh(WaterGimbalMesh);
	WaterGimbal->GimbalSpeed = WaterGimbalSpeed;
	WaterGimbal->AccelSpeed = AccelSpeed;
	WaterGimbal->TimeLineCurve = TimeLineCurve;
	WaterGimbal->Attributes = EAttributeKeyword::e_Water;

	ThunderGimbal = Cast<AGimbalPartsObject>(ChildThunderGimbal->GetChildActor());
	ThunderGimbal->Gimbal->SetStaticMesh(ThunderGimbalMesh);
	ThunderGimbal->GimbalSpeed = ThunderGimbalSpeed;
	ThunderGimbal->AccelSpeed = AccelSpeed;
	ThunderGimbal->TimeLineCurve = TimeLineCurve;
	ThunderGimbal->Attributes = EAttributeKeyword::e_Thunder;
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
	if (FireGimbal->IsGimbalOn == false) {
		//짐벌을 키고 회전 속도 가속
		
		FireGimbal->GimbalStart();
		if (WaterGimbal->IsGimbalOn == true && ThunderGimbal->IsGimbalOn == true)
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
		FireGimbal->GimbalReverse();
		//원소 게이지 상승 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

//이하동문
void AGimbalObject::WaterGimbalOnOff()
{
	//짐벌이 꺼저있으면 
	if (WaterGimbal->IsGimbalOn == false) {
		//짐벌을 키고 회전 속도 가속

		WaterGimbal->GimbalStart();
		if (FireGimbal->IsGimbalOn == true && ThunderGimbal->IsGimbalOn == true)
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
		WaterGimbal->GimbalReverse();
		//원소 게이지 상승 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AGimbalObject::ThunderGimbalOnOff()
{
	//짐벌이 꺼저있으면 
	if (ThunderGimbal->IsGimbalOn == false) {
		//짐벌을 키고 회전 속도 가속

		ThunderGimbal->GimbalStart();
		if (WaterGimbal->IsGimbalOn == true && FireGimbal->IsGimbalOn == true)
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
		ThunderGimbal->GimbalReverse();
		//원소 게이지 상승 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}




