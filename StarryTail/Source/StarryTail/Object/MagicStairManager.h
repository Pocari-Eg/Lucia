// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "Trigger/MagicStairTrigger.h"
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
	AMagicStairTrigger* StartTrigger;


	UPROPERTY(EditAnywhere, Category = Trigger)
	AMagicStairTrigger* EndTrigger;

private:
	float min = 2000.0f;
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
	UFUNCTION(BluePrintCallAble)
	void OnStair();

	UFUNCTION(BluePrintCallAble)
	void TriggerOn();
	UFUNCTION(BluePrintCallAble)
	void TriggerOff();

private:
	void TickStart();
	void TickEnd();
};
