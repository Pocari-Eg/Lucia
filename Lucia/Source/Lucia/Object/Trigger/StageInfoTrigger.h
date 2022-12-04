// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Lucia.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "StageInfoTrigger.generated.h"

UCLASS()
class LUCIA_API AStageInfoTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageInfoTrigger();
	//충돌 트리거
	UPROPERTY(EditAnywhere, Category = Trigger)
		UBoxComponent* Trigger;
	//메쉬
	UPROPERTY(EditAnywhere, Category = Trigger)
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = Title)
	FText TitleText;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//충돌 체크
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	//트리거 Off
	void TriggerOff();
};
