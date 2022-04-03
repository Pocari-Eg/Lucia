// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"

#include "OccupiedObject.h"
#include "Components/ChildActorComponent.h"
#include "GimbalObject.generated.h"



UCLASS()
class STARRYTAIL_API AGimbalObject : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* Center;

	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UStaticMeshComponent* FireGimbal;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UStaticMeshComponent* WaterGimbal;
	UPROPERTY(EditAnyWhere,Category=GIMBAL)
	UStaticMeshComponent* ThunderGimbal;


	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float FireGimbalSpeed;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float WaterGimbalSpeed;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float ThunderGimbalSpeed;


	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* FireOccupiedArea;
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* WaterOccupiedArea;
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* ThungerOccupiedArea;
private:

	UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  MaxAttributesGauge;
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  CurrentAttributesGauge;
	UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  AttributesGaugeNum;



	bool IsFireGimbalOn;
	bool IsWaterGimbalOn;
	bool IsThunderGimbalOn;

	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	bool IsAllGimbalOn;

	// Timer
	FTimerHandle TimerHandle;
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
	void FireGimbalOnOff();
	void WaterGimbalOnOff();
	void ThunderGimbalOnOff();



	void GimbalGaugeOn();
};
