// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "MagicStairTrigger.h"
#include "MagicStairManager.generated.h"

UCLASS()
class STARRYTAIL_API AMagicStairManager : public AActor
{
	GENERATED_BODY()
public:
	//충돌 트리거
	UPROPERTY(EditAnywhere, Category = Stair)
	TArray<AActor*> StairArray;
	

	UPROPERTY(EditAnywhere, Category = Trigger)
	AMagicStairTrigger* FirstTrigger;


	UPROPERTY(EditAnywhere, Category = Trigger)
	AMagicStairTrigger* SecondTrigger;

private:
	TArray<UMaterialInstanceDynamic*> NewMaterial;
public:	
	// Sets default values for this actor's properties
	AMagicStairManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void MagicStairControl();
};
