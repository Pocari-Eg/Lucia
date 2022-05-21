// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include"EnemySpawnPoint.h"
#include "EnemySpawnTrigger.generated.h"

UCLASS()
class STARRYTAIL_API AEnemySpawnTrigger : public AActor
{
	GENERATED_BODY()
	
private:
	int32 WaveMonsterCount;

	ULevelSequencePlayer* SequncePlayer;

	bool IsCurrentSpawn;
public:
	UPROPERTY(EditAnywhere, Category = Trigger)
		UBoxComponent* Trigger;
	//메쉬
	UPROPERTY(EditAnywhere, Category = Trigger)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = SpawnPoint)
	 TArray<AEnemySpawnPoint*> SpawnPoint;

	UPROPERTY(EditAnywhere, Category = SpawnPoint, meta = (ClampMin = "0", ClampMax = "100"))
	int32 NextWavePercent;

	UPROPERTY(EditAnywhere, Category = Sequence)
	ALevelSequenceActor* SequenceActor;
	//Function
public:
	// Sets default values for this actor's properties
	AEnemySpawnTrigger();

	//충돌 체크
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//트리거 Off
	void TriggerOff();
	//트리거 On
	void TriggerOn();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void WaveManager();
	void WaveStart();
	void WaveClear();
};
