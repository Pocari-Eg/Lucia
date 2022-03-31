// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "GimbalPartsObject.generated.h"
UCLASS()
class STARRYTAIL_API AGimbalPartsObject : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnyWhere,Category=INFO)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnyWhere, Category = INFO)
	EAttributeKeyword Attribute;
	UPROPERTY(EditAnyWhere, Category = INFO)
	float Speed;

	URotatingMovementComponent* Movement;
	UPROPERTY(EditAnyWhere, Category = ROTATION)
	bool Pitch;
	UPROPERTY(EditAnyWhere, Category = ROTATION)
	bool Yaw;
	UPROPERTY(EditAnyWhere, Category = ROTATION)
		bool Roll;

public:	
	// Sets default values for this actor's properties
	AGimbalPartsObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetRotation();
};
