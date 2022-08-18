// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceTrigger.h"

// Sets default values
ASequenceTrigger::ASequenceTrigger()
{
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

	PlayType = ESequenePlayType::Play;

}

void ASequenceTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (SequenceActor.Num() != 0)
	{
		for (int i = 0; i < SequenceActor.Num(); i++)
		{
			
		
			if (SequenceActor[i] != nullptr) {
				switch (PlayType)
				{
				case ESequenePlayType::Play:
					if (!SequenceActor[i]->SequencePlayer->IsPlaying())
						SequenceActor[i]->SequencePlayer->Play();
					break;
				case ESequenePlayType::Reverse:
					SequenceActor[i]->SequencePlayer->PlayReverse();
					break;
				default:
					break;
				}
			}
			
		}
	}
	TriggerOff();
}

// Called when the game starts or when spawned
void ASequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ASequenceTrigger::OnBeginOverlap);
	
}

void ASequenceTrigger::TriggerOff()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(false);
}

void ASequenceTrigger::TriggerOn()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(true);
}





