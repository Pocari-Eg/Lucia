// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiritPlate.h"

// Sets default values
ASpiritPlate::ASpiritPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ASpiritPlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiritPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

