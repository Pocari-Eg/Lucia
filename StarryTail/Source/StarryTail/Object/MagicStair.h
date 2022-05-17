// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MagicStair.generated.h"

UCLASS()
class STARRYTAIL_API AMagicStair : public AActor
{
	GENERATED_BODY()
public:

	//�浹 Ʈ����
	UPROPERTY(EditAnywhere, Category = Trigger)
		UBoxComponent* Trigger;
	//�޽�
	UPROPERTY(EditAnywhere, Category = Trigger)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Stair)
		TArray<AActor*> StairArray;

public:
	// Sets default values for this actor's properties
	AMagicStair();

	virtual void Tick(float DeltaTime) override;

	//�浹 üũ
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
