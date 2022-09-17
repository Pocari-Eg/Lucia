// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "../STGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = Mesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_MESH(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	if (SM_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(SM_MESH.Object);
	}
	OldRadius = 0.0f;
	CurrentWave = 0;

	Group_Range_Radius = 800.0f;

	BattleMonster = nullptr;

	 SupportNum = 0;
	 SpawnNum = 0;
}

void AEnemySpawnPoint::RandomSpawn()
{
	auto Instance = Cast<USTGameInstance>(GetGameInstance());
		for (int Monster_Index = 0; Monster_Index < SpawnWave[CurrentWave].Monster.Num(); Monster_Index++)
		{
			for (int SpawnCount = 0; SpawnCount < SpawnWave[CurrentWave].Monster[Monster_Index].Count; SpawnCount++)
			{
				//중심 기준 반경의 원 안에 랜덤 포인트
				FVector2D random = FMath::RandPointInCircle(Radius); 

				//새로운 좌표 생성
				FVector SpawnLocation = GetActorLocation() + FVector(random, 100.0f);

				

				//새로운 몬스터 생성
				AMonster* NewMonster=GetWorld()->SpawnActor<AMonster>(SpawnWave[CurrentWave].Monster[Monster_Index].Type, FVector(9999,9999,9999), FRotator::ZeroRotator); 

				if (NewMonster != nullptr) {
					NewMonster->SetActorLocation(SpawnLocation);
					NewMonster->SetSpawnPos();
					NewMonster->OnSpawnEffectEvent();

					//플레이어를 바라보도록
					FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(NewMonster->GetLocation(),
						UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
					NewMonster->SetActorRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));

					NewMonster->SetSpawnEnemy();
					NewMonster->SetMonsterContorl(this);
					SpawnMonsters.Add(NewMonster);
					SpawnNum++;

					if (Instance != nullptr)Instance->AddEnemyCount(NewMonster->GetRank());
				}
			}
		}

	CurrentWave++;
	CurrentWave >= SpawnWave.Num()? Instance->SetLastWave(true): Instance->SetLastWave(false);
	
}

int AEnemySpawnPoint::getWaveMonsterCount()
{
	int num = 0;
	for (int Monster_Index = 0; Monster_Index < SpawnWave[CurrentWave].Monster.Num(); Monster_Index++)
	{
		num+=SpawnWave[CurrentWave].Monster[Monster_Index].Count;
	}
	return num;
}

int AEnemySpawnPoint::getCurrentWave()
{
	return CurrentWave;
}



void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BattleMonster != nullptr) {
		FindNearMontser();
	}
}


void AEnemySpawnPoint::SetBattleMonster(AMonster* Monster)
{
	if (BattleMonster == nullptr) {

		BattleMonster = Monster;
		BattleMonster->GetAIController()->SetPlayer();
		BattleMonster->SetBattleState();
		for (int i = 0; i < SpawnMonsters.Num(); i++)
		{
			if(SpawnMonsters[i]!=nullptr)
			SpawnMonsters[i]->GetAIController()->SetBattleMonster(BattleMonster);
		}

	}

}


AMonster* AEnemySpawnPoint::GetBattleMonster()
{
	if (BattleMonster != nullptr)
	{
		return BattleMonster;
	}
	return nullptr;
}

void AEnemySpawnPoint::FindNearMontser()
{
	TArray<FOverlapResult> AnotherMonsterList = BattleMonster->DetectMonster(Group_Range_Radius);
	if (AnotherMonsterList.Num() != 0)
	{
		for (auto const& AnotherMonster : AnotherMonsterList)
		{
			auto Mob = Cast<AMonster>(AnotherMonster.GetActor());
			if (Mob == nullptr)
				continue;
			if (Mob == BattleMonster) {
				continue;
			}
			else {

				if (Mob->GetState() != EMontserState::Support) {

					Mob->SetSupportState();
				}
			}
		
		}
	}
}

void AEnemySpawnPoint::InsertSupportGroup(AMonster* Monster)
{
	SupportMonsters.Add(Monster);
	Monster->GetAIController()->SetPlayer();
	SupportNum++;
}

void AEnemySpawnPoint::InitSupportGroup()
{

	BattleMonster = nullptr;
	for (int i = 0; i < SupportNum; i++)
	{
		if (SupportMonsters[i] != nullptr)
			SupportMonsters[i]->SetNormalState();
	}

	for (int i = 0; i < SpawnNum; i++)
	{
		if (SpawnMonsters[i] != nullptr)
			SpawnMonsters[i]->GetAIController()->InitBattleMonster();
	}

	SupportMonsters.Empty();
	SupportNum = 0;
}



void AEnemySpawnPoint::DeleteMonster(AMonster* Monster)
{


	for (int i = 0; i < SupportNum; i++)
	{
		if (SupportMonsters[i] == Monster)
		{
			SupportMonsters[i] = nullptr;
		}	
	}

	for (int i = 0; i < SpawnNum; i++)
	{
		if (SpawnMonsters[i] == Monster)
		{
			SpawnMonsters[i] = nullptr;
		}
	}
}

float AEnemySpawnPoint::GetGroupRangeRadius() const
{
	return Group_Range_Radius;
}
