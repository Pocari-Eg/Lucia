// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalPartsComponent.h"

// Sets default values for this component's properties
UGimbalPartsComponent::UGimbalPartsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Movement"));
	Movement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}
	Yaw = false;
	Pitch = false;
	Roll = false;
	// ...
	
}


// Called when the game starts
void UGimbalPartsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGimbalPartsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGimbalPartsComponent::SetRotation()
{
	if (Pitch == true)Movement->RotationRate = FRotator(Speed, 0.0f, 0.0f);
	else if (Yaw == true)Movement->RotationRate = FRotator(0.0f, Speed, 0.0f);
	else if (Roll == true)Movement->RotationRate = FRotator(0.0f, 0.0f, Speed);
	else {
		Movement->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	}
}

