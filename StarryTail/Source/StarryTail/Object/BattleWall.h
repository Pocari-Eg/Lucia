// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "BattleWall.generated.h"

UCLASS()
class STARRYTAIL_API ABattleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleWall();
	UPROPERTY(EditAnywhere, Category = WAll)
	UBoxComponent* WallCollision;
	//메쉬
	UPROPERTY(EditAnywhere, Category = WAll)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = WAll)
	UParticleSystemComponent* Particle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void OnBattleWall();
	void OffBattleWall();
private:
	//트리거 Off
	void TriggerOn();
	void TriggerOff();

	void ParticleOn();
	void ParticleOff();
};
