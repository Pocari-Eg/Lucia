// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpiritPlate.h"
#include "ShieldSpirit.generated.h"

UCLASS()
class LUCIA_API AShieldSpirit : public AActor
{
	GENERATED_BODY()

//var
private:
	UPROPERTY(EditAnywhere, Category = Mesh, meta = (AllowPrivateAccess = "ture"))
	USkeletalMeshComponent* Mesh;

	ASpiritPlate* TargetPlate;
	bool bIsPetMove;
public:	
	// Sets default values for this actor's properties
	AShieldSpirit();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpiritPlate(ASpiritPlate* Target);
private:
	
	void MoveToPlate(float DeltaTime);

};
