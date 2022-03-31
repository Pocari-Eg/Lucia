// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalObject.h"

// Sets default values
AGimbalObject::AGimbalObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	RootComponent = Center;
	
	
	FireGimbal = CreateDefaultSubobject<UGimbalPartsComponent>(TEXT("FIREGIMBAL"));
	WaterObject = CreateDefaultSubobject<UGimbalPartsComponent>(TEXT("WATERGIMBAL"));
	ThunderObject = CreateDefaultSubobject<UGimbalPartsComponent>(TEXT("THUNDERGIMBAL"));

	

	FireGimbal->Mesh->SetupAttachment(Center);
	WaterObject->Mesh->SetupAttachment(Center);
	ThunderObject->Mesh->SetupAttachment(Center);


	FireGimbal->Mesh->SetRelativeLocation(GetActorLocation());
	WaterObject->Mesh->SetRelativeLocation(GetActorLocation());
	ThunderObject->Mesh->SetRelativeLocation(GetActorLocation());

	//WaterObject->Mesh->SetRelativeLocation(GetActorLocation());
	//ThunderObject->Mesh->SetRelativeLocation(GetActorLocation());
}

// Called when the game starts or when spawned
void AGimbalObject::BeginPlay()
{
	Super::BeginPlay();
	
	FireOccupiedArea->FOnOccupy.AddUObject(this, &AGimbalObject::RotateFireGimbal);
	
}

// Called every frame
void AGimbalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGimbalObject::RotateFireGimbal()
{
	FireGimbal->SetRotation();
}


