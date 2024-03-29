// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicStairTrigger.h"

// Sets default values
AMagicStairTrigger::AMagicStairTrigger()
{
	//�ʱ� ����
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("BlockAll"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

}

void AMagicStairTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnTickControl.Broadcast();
}

void AMagicStairTrigger::TriggerOn()
{
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
}

void AMagicStairTrigger::TriggerOff()
{
	Trigger->SetCollisionProfileName(TEXT("BlockAll"));
}

void AMagicStairTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMagicStairTrigger::OnBeginOverlap);
}




