// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterBasicAttack.generated.h"

class AIreneCharacter;

UCLASS()
class STARRYTAIL_API AWaterBasicAttack : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;
	float LifeTime;
public:
	UPROPERTY()
	AIreneCharacter* Irene;
private:
	
public:	
	// Sets default values for this actor's properties
	AWaterBasicAttack();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
