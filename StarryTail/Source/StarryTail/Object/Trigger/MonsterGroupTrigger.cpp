// Fill out your copyright notice in the Description page of Project Settings.
#include "MonsterGroupTrigger.h"
#include"../../STGameInstance.h"


// Sets default values
AMonsterGroupTrigger::AMonsterGroupTrigger()
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

	CurrentWave = 0;
}

void AMonsterGroupTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)
	{
		Instance->InitData();
	}

	TriggerOff();
	if (WAVE.Num() != 0) {
		WaveStart();
		if (StartSequenceActor.Num() != 0)
		{
			for (int i = 0; i < StartSequenceActor.Num(); i++) {
				StartSequenceActor[i]->SequencePlayer->Play();
			}
		}
	}

}

// Called when the game starts or when spawned
void AMonsterGroupTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMonsterGroupTrigger::OnBeginOverlap);

	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)
	{
		Instance->WaveStart.AddUObject(this, &AMonsterGroupTrigger::WaveManager);
		Instance->SetNextWaveCount(0);
	}

}

void AMonsterGroupTrigger::WaveManager()
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

void AMonsterGroupTrigger::WaveStart()
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (CurrentWave<WAVE.Num()) {
		WaveMonsterCount = 0;
		OnBattleWall();
		if (WAVE.Num() != 0) {

				if (WAVE[CurrentWave].Monster.Num() != 0) {
					WaveMonsterCount = WAVE[CurrentWave].Monster.Num();
					
					for (int j = 0; j < WaveMonsterCount; j++)
					{
						WAVE[CurrentWave].Monster[j]->SetGroup();
						
						if (Instance != nullptr)Instance->AddEnemyCount(WAVE[CurrentWave].Monster[j]->GetRank());
					}

				}
		
		}
		CurrentWave++;
		CurrentWave >= WAVE.Num() ? Instance->SetLastWave(true) : Instance->SetLastWave(false);
	}
}

void AMonsterGroupTrigger::WaveClear()
{
	STARRYLOG(Warning, TEXT("Wave Clear"));
	OffBattleWall();
	if (SequenceActor.Num() != 0)
	{
		for (int i = 0; i < SequenceActor.Num(); i++) {
			SequenceActor[i]->SequencePlayer->Play();
		}
	}

	if (LabMagic != nullptr)
	{
		LabMagic->EndLabMagic();
	}
}

void AMonsterGroupTrigger::OnBattleWall()
{
	if (BattleWall.Num() > 0)
	{

		for (int i = 0; i < BattleWall.Num(); i++)
		{
			BattleWall[i]->OnBattleWall();
		}
	}
}

void AMonsterGroupTrigger::OffBattleWall()
{
	if (BattleWall.Num() > 0)
	{
		for (int i = 0; i < BattleWall.Num(); i++)
		{
			BattleWall[i]->OffBattleWall();
		}
	}
}

void AMonsterGroupTrigger::TriggerOff()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(false);
}

void AMonsterGroupTrigger::TriggerOn()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(true);
}


