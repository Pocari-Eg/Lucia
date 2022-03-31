// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "Components/ActorComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "GimbalPartsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STARRYTAIL_API UGimbalPartsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnyWhere, Category = INFO)
		UStaticMeshComponent* Mesh;
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
	UGimbalPartsComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetRotation();
};
