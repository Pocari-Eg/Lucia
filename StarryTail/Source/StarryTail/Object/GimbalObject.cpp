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


	IsFireGimbalOn = false;
	IsWaterGimbalOn = false;
	IsThunderGimbalOn = false;
}

// Called when the game starts or when spawned
void AGimbalObject::BeginPlay()
{
	Super::BeginPlay();
	
	if(FireOccupiedArea!=nullptr)
		FireOccupiedArea->FOnOccupy.AddUObject(this, &AGimbalObject::FireGimbalOn);
	if (WaterOccupiedArea != nullptr)
		WaterOccupiedArea->FOnOccupy.AddUObject(this, &AGimbalObject::WaterGimbalOn);
	if (ThungerOccupiedArea != nullptr)
		ThungerOccupiedArea->FOnOccupy.AddUObject(this, &AGimbalObject::ThunderGimbalOn);
	
}

// Called every frame
void AGimbalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsFireGimbalOn == true ? FireGimbal->AddWorldRotation(FRotator(0.0f, FireGimbalSpeed, 0.0f)) : IsFireGimbalOn =false;
	IsWaterGimbalOn == true ? WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, WaterGimbalSpeed)) : IsWaterGimbalOn = false;
	IsThunderGimbalOn == true ? ThunderGimbal->AddWorldRotation(FRotator(ThunderGimbalSpeed, 0.0f, 0.0f)) : IsThunderGimbalOn = false;

}

void AGimbalObject::FireGimbalOn()
{
	IsFireGimbalOn = true;
}

void AGimbalObject::WaterGimbalOn()
{
	IsWaterGimbalOn = true;
}

void AGimbalObject::ThunderGimbalOn()
{
	IsThunderGimbalOn = true;
}




