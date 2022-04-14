// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChainLightning.generated.h"

UCLASS()
class STARRYTAIL_API AChainLightning : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChainLightning();

	void SetDamage(float Value);
	float GetDamage() const;
	void AddCount();
private:
	//Var
	TArray<FVector> MoveTargetList;
	FVector MoveDir;

	float Damage;
	float TargetCount;
	float Count;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
