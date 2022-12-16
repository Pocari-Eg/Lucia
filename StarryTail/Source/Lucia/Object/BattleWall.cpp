// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleWall.h"

// Sets default values
ABattleWall::ABattleWall()
{
	PrimaryActorTick.bCanEverTick = false;
	WallCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall"));

	RootComponent = WallCollision;

	WallCollision->SetCollisionProfileName(TEXT("NoCollision"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	Particle->SetupAttachment(RootComponent);
	Particle->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
}


// Called when the game starts or when spawned
void ABattleWall::BeginPlay()
{
	Super::BeginPlay();
	WallCollision->SetGenerateOverlapEvents(false);
	OffBattleWall();
}

void ABattleWall::OnBattleWall()
{
	ParticleOn();
	TriggerOn();
}

void ABattleWall::OffBattleWall()
{
	ParticleOff();
	TriggerOff();
}

void ABattleWall::TriggerOn()
{
	WallCollision->SetCollisionProfileName(TEXT("BlockAll"));
}

void ABattleWall::TriggerOff()
{
	WallCollision->SetCollisionProfileName(TEXT("NoCollision"));
}

void ABattleWall::ParticleOn()
{
	Particle->SetVisibility(true);
}

void ABattleWall::ParticleOff()
{
	Particle->SetVisibility(false);
}

