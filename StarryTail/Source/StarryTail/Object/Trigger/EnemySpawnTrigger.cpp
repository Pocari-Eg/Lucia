// Fill out your copyright notice in the Description page of Project Settings.
#include "EnemySpawnTrigger.h"
#include"../../STGameInstance.h"


// Sets default values
AEnemySpawnTrigger::AEnemySpawnTrigger()
{
	//초기 설정
	PrimaryActorTick.bCanEverTick = true;
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

	IsCurrentSpawn = false;
}

void AEnemySpawnTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG(Warning, TEXT("Monster Trigger Overlap"));
	TriggerOff();
	if (SpawnPoint.Num() != 0) {
		WaveStart();
		if (StartSequenceActor.Num()!=0)
		{
			for (int i = 0; i < StartSequenceActor.Num(); i++) {
				StartSequenceActor[i]->SequencePlayer->Play();
			}
		}
	}

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
void AEnemySpawnTrigger::Tick(float DeltaTime)
{
	AMonsterController::Tick(DeltaTime);
}
void AEnemySpawnTrigger::WaveManager()
{

	if (IsCurrentSpawn == true) {
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
}

void AEnemySpawnTrigger::WaveStart()
{

	TArray<AMonster*> SpawnMonsters;

	if (SpawnPoint[0]->getCurrentWave() < SpawnPoint[0]->SpawnWave.Num()) {
		WaveMonsterCount = 0;
		OnBattleWall();
		if (SpawnPoint.Num() != 0) {
			for (int i = 0; i < SpawnPoint.Num(); i++)
			{
				if (SpawnPoint[i] != nullptr) {
					WaveMonsterCount += SpawnPoint[i]->getWaveMonsterCount();
					SpawnPoint[i]->RandomSpawn();
					
					SpawnMonsters += SpawnPoint[i]->GetCurWaveMonster();
				}
			}
		}
		SetCurWaveMonsters(SpawnMonsters);

		SetCloseMonster();
		auto Instance = Cast<USTGameInstance>(GetGameInstance());
		if (Instance != nullptr)
		{
			Instance->SetNextWaveCount(WaveMonsterCount * NextWavePercent / 100);
		}
		
	}


}

void AEnemySpawnTrigger::WaveClear()
{
	STARRYLOG(Warning, TEXT("Wave Clear"));
	OffBattleWall();
	IsCurrentSpawn = false;
	if (SequenceActor.Num() != 0)
	{
		for (int i = 0; i < SequenceActor.Num(); i++) {
			SequenceActor[i]->SequencePlayer->Play();
		}
	}
}

void AEnemySpawnTrigger::OnBattleWall()
{
	if (BattleWall.Num() > 0)
	{

		for (int i = 0; i < BattleWall.Num(); i++)
		{
			BattleWall[i]->OnBattleWall();
		}
	}
}

void AEnemySpawnTrigger::OffBattleWall()
{
	if (BattleWall.Num() > 0)
	{
		for (int i = 0; i < BattleWall.Num(); i++)
		{
			BattleWall[i]->OffBattleWall();
		}
	}
}

void AEnemySpawnTrigger::TriggerOff()
{
	//트리거 충돌을 켜기
	IsCurrentSpawn = true;
	Trigger->SetGenerateOverlapEvents(false);
}

void AEnemySpawnTrigger::TriggerOn()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(true);
}


