// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Swirl.h"
#include "Tornado.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API ATornado : public ASwirl
{
	GENERATED_BODY()
private:


	
	float RotationTimer;
	float RotationTime;

	bool bIsGuidedMove;

public:
	ATornado();
	void SwirlCoreActive(FVector MoveDirectionVal);

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void  TornadoPullRangeBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void  TornadoPullRangeEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
