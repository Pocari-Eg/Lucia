// Fill out your copyright notice in the Description page of Project Settings.


#include "TelePortPoint.h"

// Sets default values
ATelePortPoint::ATelePortPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Mesh;
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Particle->SetupAttachment(RootComponent);
	Particle->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
	Particle->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ATelePortPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATelePortPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATelePortPoint::TelePortSignActive()
{
	
	Particle->SetActive(true, true);
}

void ATelePortPoint::TelePortSignDeactivate()
{
	Particle->Deactivate();
}

