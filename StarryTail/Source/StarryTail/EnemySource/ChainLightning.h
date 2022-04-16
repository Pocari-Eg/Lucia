// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../StarryTail.h"
#include "ChainLightning.generated.h"

UCLASS()
class STARRYTAIL_API AChainLightning : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChainLightning();
	void Init();


	void SetDamage(float Value);
	float GetDamage() const;
	void SetMoveSpeed(float Value);
	void AddCount();
private:
	//Function
	void CheckDistance();
	//Var
	USphereComponent* Collision;

	TArray<FVector> MoveTargetList;
	FVector MoveDir;
	FVector NewLocation;

	float Damage;
	float MoveSpeed;
	int TargetCount;
	int Count;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
