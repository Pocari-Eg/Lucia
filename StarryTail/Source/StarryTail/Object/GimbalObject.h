// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"

#include "OccupiedObject.h"
#include "GimbalPartsComponent.h"
#include "GimbalObject.generated.h"



UCLASS()
class STARRYTAIL_API AGimbalObject : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* Center;

	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UGimbalPartsComponent* FireGimbal;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UGimbalPartsComponent* WaterObject;
	UPROPERTY(EditAnyWhere,Category=GIMBAL)
	UGimbalPartsComponent* ThunderObject;

	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* FireOccupiedArea;

public:	
	// Sets default values for this actor's properties
	AGimbalObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void RotateFireGimbal();
};
