// Fill out your copyright notice in the Description page of Project Settings.


#include "DropFloorEffect.h"

// Sets default values
ADropFloorEffect::ADropFloorEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DropEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DropEffect"));
	DropEffect->SetupAttachment(RootComponent);
	DropEffect->SetWorldScale3D(FVector(1.0f));

	InitialLifeSpan = 2.0f;
}
void ADropFloorEffect::SetEffect(UParticleSystem* ParticleSystem)
{
	DropEffect->SetTemplate(ParticleSystem);
}
// Called when the game starts or when spawned
void ADropFloorEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropFloorEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

