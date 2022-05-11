// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnTrigger.h"

// Sets default values
AEnemySpawnTrigger::AEnemySpawnTrigger()
{
	//�ʱ� ����
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

void AEnemySpawnTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG(Warning, TEXT("Monster Trigger Overlap"));

	if (SpawnPoint.Num() != 0) {
		for (int i = 0; i < SpawnPoint.Num(); i++)
		{
			if(SpawnPoint[i]!=nullptr)
			SpawnPoint[i]->RandomSpawn();
		}
	}
}

// Called when the game starts or when spawned
void AEnemySpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawnTrigger::OnBeginOverlap);
	
}

void AEnemySpawnTrigger::TriggerOff()
{
	//Ʈ���� �浹�� �ѱ�
	Trigger->SetGenerateOverlapEvents(false);
}

void AEnemySpawnTrigger::TriggerOn()
{
	//Ʈ���� �浹�� �ѱ�
	Trigger->SetGenerateOverlapEvents(true);
}


