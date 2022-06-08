// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "../STGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include <Engine/Classes/Kismet/KismetMathLibrary.h>
#include "../EnemySource/Morbit/Morbit.h"
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
				FVector SpawnLocation = GetActorLocation() + FVector(random, 130.0f);

				

				//새로운 몬스터 생성
				AMonster* NewMonster=GetWorld()->SpawnActor<AMonster>(SpawnWave[CurrentWave].Monster[Monster_Index].Type, GetActorLocation(), FRotator::ZeroRotator); 

				if (NewMonster != nullptr) {
					NewMonster->SetActorLocation(SpawnLocation);
					NewMonster->SetSpawnPos();
					NewMonster->OnSpawnEffectEvent();

					//플레이어를 바라보도록
					FRotator CameraRot = UKismetMathLibrary::FindLookAtRotation(NewMonster->GetLocation(),
						UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
					NewMonster->SetActorRotation(FRotator(0.0f, CameraRot.Yaw, 0.0f));

					NewMonster->SetSpawnEnemy();

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
}
  