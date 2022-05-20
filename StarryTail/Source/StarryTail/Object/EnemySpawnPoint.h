// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "../EnemySource/Monster.h"
#include "EnemySpawnPoint.generated.h"

#pragma region WaveData
USTRUCT()
struct FMonsterData {
public:
	GENERATED_BODY()
	UPROPERTY(EditAnyWhere)
	int32 Count;
	UPROPERTY(EditAnyWhere)
	TSubclassOf<AMonster> Type;
};
USTRUCT()
struct FWaveData {
public:
	GENERATED_BODY()
  UPROPERTY(EditAnyWhere)
  TArray<FMonsterData> Monster;
};
#pragma endregion WaveData

UCLASS()
class STARRYTAIL_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = SPAWN)
	TArray<FWaveData> SpawnWave;
private:
	//메쉬
    UPROPERTY(VisibleAnyWhere, Category = Mesh, meta=(AllowPrivateAccess="ture"))
	UStaticMeshComponent* Mesh;
	//몬스터 소환 반경
	UPROPERTY(EditAnyWhere, Category = SPAWN, meta = (AllowPrivateAccess = "ture"))
	float Radius;

	//전 몬스터 소환 반경 
	float OldRadius;

	//현재 몬스터 웨이브
	int32 CurrentWave;
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();
	void RandomSpawn();

	int getWaveMonsterCount();
	int getCurrentWave();

	virtual void Tick(float DeltaTime) override;


private:
	void DrawSpawnArea();
};
