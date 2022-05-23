// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../StarryTail.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "DialogTrigger.generated.h"

UCLASS()
class STARRYTAIL_API ADialogTrigger : public AActor
{
	GENERATED_BODY()
	
		//�浹 Ʈ����
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;
	//�޽�
	UPROPERTY(EditAnywhere, Category = Trigger)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = Dialog)
	FString DialogText;


public:
	// Sets default values for this actor's properties
	ADialogTrigger();

	//�浹 üũ
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Ʈ���� Off
	void TriggerOff();
	//Ʈ���� On
	void TriggerOn();
};
