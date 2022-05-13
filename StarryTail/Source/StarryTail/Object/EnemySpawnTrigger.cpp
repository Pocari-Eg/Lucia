// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemySpawnTrigger.h"
#include"../STGameInstance.h"


// Sets default values
AEnemySpawnTrigger::AEnemySpawnTrigger()
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

}

void AEnemySpawnTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG(Warning, TEXT("Monster Trigger Overlap"));
	TriggerOff();
	if(SpawnPoint.Num()!=0)
	WaveStart();
}

// Called when the game starts or when spawned
void AEnemySpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEnemySpawnTrigger::OnBeginOverlap);

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)
	{
		Instance->WaveStart.AddUObject(this ,&AEnemySpawnTrigger::WaveManager);
	}
	
}

void AEnemySpawnTrigger::WaveManager()
{

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)
	{
		if (Instance->IsLastWave())
		{
			WaveClear();
		}
		else {
			WaveStart();
		}
	}

}

void AEnemySpawnTrigger::WaveStart()
{
	if (SpawnPoint[0]->getCurrentWave() < SpawnPoint[0]->SpawnWave.Num()) {
		WaveMonsterCount = 0;

		if (SpawnPoint.Num() != 0) {
			for (int i = 0; i < SpawnPoint.Num(); i++)
			{
				if (SpawnPoint[i] != nullptr) {
					WaveMonsterCount += SpawnPoint[i]->getWaveMonsterCount();
					SpawnPoint[i]->RandomSpawn();
				}
			}
		}



		auto Instance = Cast<USTGameInstance>(GetGameInstance());
		if (Instance != nullptr)
		{
			Instance->SetNextWaveCount(WaveMonsterCount * NextWavePercent / 100);
		}
	}
}

void AEnemySpawnTrigger::WaveClear()
{
	STARRYLOG(Error, TEXT("WAVE CLEAR"));
}





void AEnemySpawnTrigger::TriggerOff()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(false);
}

void AEnemySpawnTrigger::TriggerOn()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(true);
}


