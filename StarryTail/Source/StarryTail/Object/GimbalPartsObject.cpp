// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalPartsObject.h"

// Sets default values
AGimbalPartsObject::AGimbalPartsObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Movement"));
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}
	Yaw = false;
	Pitch = false;
	Roll = false;
	
}

// Called when the game starts or when spawned
void AGimbalPartsObject::BeginPlay()
{
	Super::BeginPlay();
	SetRotation();
}

// Called every frame
void AGimbalPartsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGimbalPartsObject::SetRotation()
{
	if (Pitch==true)Movement->RotationRate = FRotator(Speed, 0.0f, 0.0f);
	else if (Yaw==true)Movement->RotationRate = FRotator(0.0f, Speed, 0.0f);
	else if (Roll==true)Movement->RotationRate = FRotator(0.0f, 0.0f, Speed);
	else {
		Movement->RotationRate= FRotator(0.0f, 0.0f, 0.0f);
	}
}

