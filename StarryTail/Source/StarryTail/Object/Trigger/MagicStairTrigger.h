// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "MagicStairTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTickControlDelegate);

UCLASS()
class STARRYTAIL_API AMagicStairTrigger : public AActor
{
	GENERATED_BODY()
	
	//�浹 Ʈ����
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;
	//�޽�
	UPROPERTY(EditAnywhere, Category = Trigger)
	UStaticMeshComponent* Mesh;


public:
	// Sets default values for this actor's properties
	AMagicStairTrigger();
	FOnTickControlDelegate OnTickControl;
	//�浹 üũ
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Blueprintcallable)
	void TriggerOn();
	UFUNCTION(Blueprintcallable)
	void TriggerOff();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
