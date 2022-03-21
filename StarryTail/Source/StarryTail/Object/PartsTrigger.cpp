// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsTrigger.h"
#include "PartsObject.h"
// Sets default values
APartsTrigger::APartsTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void APartsTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APartsTrigger::OnBeginOverlap);

}

void APartsTrigger::TriggerOff()
{
	Trigger->SetGenerateOverlapEvents(false);
}

void APartsTrigger::TriggerOn()
{
	Trigger->SetGenerateOverlapEvents(true);
}

void APartsTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsStartTrigger) {
		UE_LOG(LogTemp, Error, TEXT("StartTrigger Hit"));
		if (StartObject != nullptr)
		{
			StartObject->ForwardMove(this);
			TriggerOff();
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("EndTrigger Hit"));
		if (EndObject != nullptr)
		{
			EndObject->IsEndTriggerOn = true;
			TriggerOff();
		}
	}
}