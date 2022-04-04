// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"

#include "OccupiedObject.h"
#include "Components/TimeLineComponent.h"

#include "GimbalObject.generated.h"



UCLASS()
class STARRYTAIL_API AGimbalObject : public AActor
{
	GENERATED_BODY()
	
public:
	//중앙 지점 설정
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* Center;

	//각각 속성 메쉬
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UStaticMeshComponent* FireGimbal;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UStaticMeshComponent* WaterGimbal;
	UPROPERTY(EditAnyWhere,Category=GIMBAL)
	UStaticMeshComponent* ThunderGimbal;

	//각각 속성별 회전 속도
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float FireGimbalSpeed;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float WaterGimbalSpeed;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float ThunderGimbalSpeed;

	//가속 속도
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float AccelSpeed;

	//점령지 설정
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* FireOccupiedArea;
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* WaterOccupiedArea;
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* ThungerOccupiedArea;
private:

	//목표 원소 게이지
	UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  MaxAttributesGauge;
	//현재 원소 게이지
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  CurrentAttributesGauge;
	//증가할 원소 게이지
	UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  AttributesGaugeNum;


	//현재 짐벌 상태
	bool IsFireGimbalOn;
	bool IsWaterGimbalOn;
	bool IsThunderGimbalOn;

	//모든 짐벌이 켜졌는지
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	bool IsAllGimbalOn;

	// Timer
	FTimerHandle TimerHandle;


	//타임 라인
	
	//타임라인 커브
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* TimeLineCurve;
	//타임라인
	FTimeline GimbalTimeline;

	//타임라인 상태
	bool IsTimeLineOn;

	float RotationAccel;
public:	
	// Sets default values for this actor's properties
	AGimbalObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	//짐벌 OnOff
	void FireGimbalOnOff();
	void WaterGimbalOnOff();
	void ThunderGimbalOnOff();


	//가속 시작
	UFUNCTION()
	void Acceleration();

	//가속 종료
	UFUNCTION()
	void AccelerationOff();
	//원소 게이지 상승
	void GimbalGaugeOn();
};
