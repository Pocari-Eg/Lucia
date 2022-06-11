// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialTrigger.h"
#include "../../PlayerSource/IreneUIManager.h"
#include "../../PlayerSource/IreneCharacter.h"

// Sets default values
ATutorialTrigger::ATutorialTrigger()
{
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
void ATutorialTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATutorialTrigger::OnBeginOverlap);
}

void ATutorialTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG_S(Error);
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {
		Irene->IreneUIManager->PlayerHud->SetTutorial(TutorialNum);
		TriggerOff();
	}

}

void ATutorialTrigger::TriggerOff()
{	
	Trigger->SetGenerateOverlapEvents(false);
}

