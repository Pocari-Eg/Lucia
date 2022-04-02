// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalObject.h"

// Sets default values
AGimbalObject::AGimbalObject()
{
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
}

// Called when the game starts or when spawned
void AGimbalObject::BeginPlay()
{
	Super::BeginPlay();
	
	if(FireOccupiedArea!=nullptr)
		FireOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::FireGimbalOnOff);
	if (WaterOccupiedArea != nullptr)
		WaterOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::WaterGimbalOnOff);
	if (ThungerOccupiedArea != nullptr)
		ThungerOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::ThunderGimbalOnOff);
	
}

// Called every frame
void AGimbalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsFireGimbalOn == true ? FireGimbal->AddWorldRotation(FRotator(0.0f, FireGimbalSpeed, 0.0f)) : FireGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	IsWaterGimbalOn == true ? WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, WaterGimbalSpeed)) : WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	IsThunderGimbalOn == true ? ThunderGimbal->AddWorldRotation(FRotator(ThunderGimbalSpeed, 0.0f, 0.0f)) : ThunderGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));

}

void AGimbalObject::FireGimbalOnOff()
{
	if (IsFireGimbalOn == false) {
		IsFireGimbalOn = true;
		if (IsWaterGimbalOn == true && IsThunderGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;
		IsFireGimbalOn = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AGimbalObject::WaterGimbalOnOff()
{
	if (IsWaterGimbalOn == false) {
		IsWaterGimbalOn = true;
		if (IsFireGimbalOn == true && IsThunderGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;

		IsWaterGimbalOn = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);

	}
}

void AGimbalObject::ThunderGimbalOnOff()
{
	if (IsThunderGimbalOn == false) {
		IsThunderGimbalOn = true;
		if (IsWaterGimbalOn == true && IsFireGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;

		IsThunderGimbalOn = false;
		GetWorldTimerManager().ClearTimer(TimerHandle);

	}
}

void AGimbalObject::GimbalGaugeOn()
{
  if (CurrentAttributesGauge>=MaxAttributesGauge){
	  GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	 else if (CurrentAttributesGauge <= MaxAttributesGauge - AttributesGaugeNum)
	{
		CurrentAttributesGauge += AttributesGaugeNum;
	}
}




