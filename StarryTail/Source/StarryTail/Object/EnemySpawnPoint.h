// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class STARRYTAIL_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnyWhere, Category = Mesh)
		UStaticMeshComponent* Mesh; // ¸Þ½¬ 
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();
	void RandomSpawn(float Radius);
};
