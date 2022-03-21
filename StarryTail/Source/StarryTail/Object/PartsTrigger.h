// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "PartsTrigger.generated.h"

class APartsObject;
UCLASS()
class STARRYTAIL_API APartsTrigger : public AActor
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = Platform)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* StartObject;

	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* EndObject;

	UPROPERTY(EditAnywhere, Category = Object)
	bool IsStartTrigger;


public:
	// Sets default values for this actor's properties
	APartsTrigger();
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void TriggerOff();
	void TriggerOn();

};
