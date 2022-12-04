// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "TelePortPoint.generated.h"

UCLASS()
class LUCIA_API ATelePortPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelePortPoint();
	UPROPERTY(EditAnywhere, Category = WAll)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = WAll)
	UParticleSystemComponent* Particle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void TelePortSignActive();
	void TelePortSignDeactivate();

};
