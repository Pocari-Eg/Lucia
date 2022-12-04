// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TutorialTrigger.generated.h"

UCLASS()
class LUCIA_API ATutorialTrigger : public AActor
{
	GENERATED_BODY()
public:
	//충돌 트리거
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;
	//메쉬
	UPROPERTY(EditAnywhere, Category = Trigger)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Tutoiral)
	FString TutorialNum;
public:	
	// Sets default values for this actor's properties
	ATutorialTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
private:
	void TriggerOff();
};
