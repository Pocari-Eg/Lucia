// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../StarryTail.h"
#include "GameFramework/Actor.h"
#include "GimbalPartsObject.h"
#include "OccupiedObject.h"
#include "Components/ChildActorComponent.h"

#include "EnemySpawnPoint.h"
#include "GimbalObject.generated.h"



UCLASS()
class STARRYTAIL_API AGimbalObject : public AActor
{
	GENERATED_BODY()
	
public:
	//중앙 지점 설정
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* Center;

	//각각 속성 ChildActor
	UPROPERTY(EditAnyWhere)
	UChildActorComponent* ChildFireGimbal;
	UPROPERTY(EditAnyWhere)
	UChildActorComponent* ChildWaterGimbal;
	UPROPERTY(EditAnyWhere)
	UChildActorComponent* ChildThunderGimbal;

	//각각 속성 메쉬
	UPROPERTY(EditAnyWhere, Category = MESH)
	UStaticMesh* FireGimbalMesh;
	UPROPERTY(EditAnyWhere, Category = MESH)
	UStaticMesh* WaterGimbalMesh;
	UPROPERTY(EditAnyWhere,Category = MESH)
	UStaticMesh* ThunderGimbalMesh;

	//각각 속성 짐벌
	UPROPERTY(VisibleAnywhere, Category = GIMBAL)
	AGimbalPartsObject* FireGimbal;
	UPROPERTY(VisibleAnywhere, Category = GIMBAL)
	AGimbalPartsObject* WaterGimbal;
	UPROPERTY(VisibleAnywhere, Category = GIMBAL)
	AGimbalPartsObject* ThunderGimbal;

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


	//몬스터 스폰 반경
	UPROPERTY(EditAnyWhere, Category = SPAWN)
	float SpawnRadius;

	//몬스터 스폰 위치 
	UPROPERTY(EditAnyWhere, Category = SPAWN)
	TArray<AEnemySpawnPoint*> EnemySpawnPoint;

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
	bool IsWaterGimbalOn;
	bool IsThunderGimbalOn;

	//모든 짐벌이 켜졌는지
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	bool IsAllGimbalOn;

	// Timer
	FTimerHandle TimerHandle;

	//타임라인 커브
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* TimeLineCurve;

public:	
	// Sets default values for this actor's properties
	AGimbalObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
private:
	//짐벌 OnOff
	void FireGimbalOnOff();
	void WaterGimbalOnOff();
	void ThunderGimbalOnOff();

	//원소 게이지 상승
	void GimbalGaugeOn();

	//적 스폰
	void SpawnEnemy();
};
