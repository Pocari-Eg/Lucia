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
	
	//충돌 트리거
	UPROPERTY(EditAnywhere, Category = Trigger)
	UBoxComponent* Trigger;

	//메쉬
	UPROPERTY(EditAnywhere, Category = Platform)
	UStaticMeshComponent* Mesh;

	//처음 시작 파츠오브젝트
	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* StartObject;

	//마지막 파츠 오브젝트
	UPROPERTY(EditAnywhere, Category = Object)
	APartsObject* EndObject;

	//이 트리거가 시작 트리거 인지
	UPROPERTY(EditAnywhere, Category = Object)
	bool IsStartTrigger;


public:
	// Sets default values for this actor's properties
	APartsTrigger();

	//충돌 체크
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//트리거 Off
	void TriggerOff();
	//트리거 On
	void TriggerOn();

};
