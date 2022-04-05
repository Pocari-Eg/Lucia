// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "OccupiedObject.h"
#include "Components/TimeLineComponent.h"
#include "GimbalPartsObject.generated.h"

UCLASS()
class STARRYTAIL_API AGimbalPartsObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGimbalPartsObject();
	// 메쉬
	UStaticMeshComponent* Gimbal;
	//회전 속도
	float GimbalSpeed;
	//가속 속도
	float AccelSpeed;
	//현재 짐벌 상태
	bool IsGimbalOn;

	//타임라인 커브
	UCurveFloat* TimeLineCurve;

	//타임라인
	FTimeline GimbalTimeline;

	//타임라인 상태
	bool IsTimeLineOn;

	float RotationAccel;

	EAttributeKeyword Attributes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//짐벌 Start Reverse
	void GimbalStart();
	void GimbalReverse();
private :
	
		//가속 시작
	UFUNCTION()
		void Acceleration();

	//가속 종료
	UFUNCTION()
		void AccelerationOff();

};
