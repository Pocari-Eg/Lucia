// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkPoint.h"

// Sets default values
AWalkPoint::AWalkPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
}

// Called when the game starts or when spawned
void AWalkPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

