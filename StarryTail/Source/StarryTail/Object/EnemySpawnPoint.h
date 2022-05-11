// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class STARRYTAIL_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
private:
	//메쉬
    UPROPERTY(VisibleAnyWhere, Category = Mesh, meta=(AllowPrivateAccess="ture"))
	UStaticMeshComponent* Mesh;
	//반경
	UPROPERTY(EditAnyWhere, Category = SPAWN, meta = (AllowPrivateAccess = "ture"))
	float Radius;

	float OldRadius;
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();
	void RandomSpawn();
	void RandomSpawn(float Radius);

	virtual void Tick(float DeltaTime) override;

private:
	void DrawSpawnArea();
};
