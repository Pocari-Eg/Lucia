// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include "SequenceTrigger.generated.h"

UCLASS()
class STARRYTAIL_API ASequenceTrigger : public AActor
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
	ASequenceTrigger();

	UPROPERTY(EditAnywhere, Category = Sequence)
	TArray<ALevelSequenceActor*> SequenceActor;
	//�浹 üũ
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Ʈ���� Off
	void TriggerOff();
	//Ʈ���� On
	void TriggerOn();

};
