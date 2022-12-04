// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Lucia.h"
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
class LUCIA_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = SPAWN)
	TArray<FWaveData> SpawnWave;
private:
	//�޽�
    UPROPERTY(VisibleAnyWhere, Category = Mesh, meta=(AllowPrivateAccess="ture"))
	UStaticMeshComponent* Mesh;
	//���� ��ȯ �ݰ�
	UPROPERTY(EditAnyWhere, Category = SPAWN, meta = (AllowPrivateAccess = "ture"))
	float Radius;

	//�� ���� ��ȯ �ݰ� 
	float OldRadius;

	//���� ���� ���̺�
	int32 CurrentWave;

	int32 SpawnNum;


	UPROPERTY(EditAnyWhere, Category = SPAWN, meta = (AllowPrivateAccess = "ture"))
	TArray<AMonster*> SpawnMonsters;

public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();
	void RandomSpawn();


	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


	int getWaveMonsterCount();
	int getCurrentWave();


	TArray<AMonster*> GetCurWaveMonster();

   UPROPERTY(EditAnyWhere, Category = SPAWN, meta = (AllowPrivateAccess = "ture"))
   AMonster* BattleMonster;
};
