// Fill out your copyright notice in the Description page of Project Settings.


#include "BGMChangeTrigger.h"

// Sets default values
ABGMChangeTrigger::ABGMChangeTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//초기 설정
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
}

// Called when the game starts or when spawned
void ABGMChangeTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ABGMChangeTrigger::OnBeginOverlap);
}


void ABGMChangeTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

if (SoundPlayer != nullptr) {

		switch (AreaName)
		{
		case EState::e_MainHall:
			SoundPlayer->ChangeBgm(0.0f);
				break;
		case EState::e_Library:
			SoundPlayer->ChangeBgm(1.0f);
				break;
		case EState::e_Orgranism:
			SoundPlayer->ChangeBgm(2.0f);
			break;
		default:
			break;
		}
	}
}

