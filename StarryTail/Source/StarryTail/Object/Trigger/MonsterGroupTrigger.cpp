// Fill out your copyright notice in the Description page of Project Settings.
#include "MonsterGroupTrigger.h"
#include"../../STGameInstance.h"
#include "GameFramework/GameModeBase.h"

// Sets default values
AMonsterGroupTrigger::AMonsterGroupTrigger()
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
	CurrentWave = 0;
	bIsOn = false;
}

void AMonsterGroupTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (Instance != nullptr)
	{
		Instance->InitData();
		STARRYLOG(Warning,TEXT("%s"),*GetName());
		if(GetName() == FString("MonsterGroupTrigger3"))//Instance->GetSpawnTransform().GetTranslation() == Instance->FirstPosition())
		{
			Instance->SetSpawnTransform(FTransform(Instance->SecondRotation(), Instance->SecondPosition()));
			STARRYLOG_S(Warning);
		}
		if(GetName() == FString("MonsterGroupTrigger_1"))//Instance->GetSpawnTransform().GetTranslation() == Instance->SecondPosition())
		{
			STARRYLOG_S(Warning);
			Instance->SetSpawnTransform(FTransform(Instance->ThirdRotation(), Instance->ThirdPosition()));
		}
	}
	bIsOn = true;
	TriggerOff();
	if (WAVE.Num() != 0) {
		WaveStart();
		PlayBattleBgm();
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
	if (WAVE.Num() != 0) {
		for (int i = 0; i < WAVE.Num(); i++)
		{
			if (WAVE[i].Monster.Num() != 0) {

				for (int j = 0; j < WAVE[i].Monster.Num(); j++)
				{
					WAVE[i].Monster[j]->SetStatue(true);
				}

			}
		}
	}

	
	
}

void AMonsterGroupTrigger::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMonsterGroupTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterGroupTrigger::WaveManager()
{
	if (bIsOn) {

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

void AMonsterGroupTrigger::WaveStart()
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());
	if (CurrentWave<WAVE.Num()) {
		WaveMonsterCount = 0;
		OnBattleWall();

		SetCurWaveMonsters(WAVE[CurrentWave].Monster);
		if (WAVE.Num() != 0) {

				if (WAVE[CurrentWave].Monster.Num() != 0) {
					WaveMonsterCount = WAVE[CurrentWave].Monster.Num();
					
					for (int j = 0; j < WaveMonsterCount; j++)
					{
						WAVE[CurrentWave].Monster[j]->SetGroup();
						
						if (Instance != nullptr)Instance->AddEnemyCount(WAVE[CurrentWave].Monster[j]->GetRank());

						if (j == 0)
						{
							WAVE[CurrentWave].Monster[j]->SetCaptin();
						}
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
		LabMagic->EndExplosion();
		LabMagic->EndLabMagic();
	}
	bIsOn = false;

	PlayNormalBgm();
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


