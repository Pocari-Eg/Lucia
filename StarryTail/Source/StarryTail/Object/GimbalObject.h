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
	//�߾� ���� ����
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* Center;

	//���� �Ӽ� ChildActor
	UPROPERTY(EditAnyWhere)
	UChildActorComponent* ChildFireGimbal;
	UPROPERTY(EditAnyWhere)
	UChildActorComponent* ChildWaterGimbal;
	UPROPERTY(EditAnyWhere)
	UChildActorComponent* ChildThunderGimbal;

	//���� �Ӽ� �޽�
	UPROPERTY(EditAnyWhere, Category = MESH)
	UStaticMesh* FireGimbalMesh;
	UPROPERTY(EditAnyWhere, Category = MESH)
	UStaticMesh* WaterGimbalMesh;
	UPROPERTY(EditAnyWhere,Category = MESH)
	UStaticMesh* ThunderGimbalMesh;

	//���� �Ӽ� ����
	UPROPERTY(VisibleAnywhere, Category = GIMBAL)
	AGimbalPartsObject* FireGimbal;
	UPROPERTY(VisibleAnywhere, Category = GIMBAL)
	AGimbalPartsObject* WaterGimbal;
	UPROPERTY(VisibleAnywhere, Category = GIMBAL)
	AGimbalPartsObject* ThunderGimbal;

	//���� �Ӽ��� ȸ�� �ӵ�
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float FireGimbalSpeed;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float WaterGimbalSpeed;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float ThunderGimbalSpeed;

	//���� �ӵ�
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	float AccelSpeed;

	//������ ����
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* FireOccupiedArea;
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* WaterOccupiedArea;
	UPROPERTY(EditAnyWhere, Category = AREA)
	AOccupiedObject* ThungerOccupiedArea;


	//���� ���� �ݰ�
	UPROPERTY(EditAnyWhere, Category = SPAWN)
	float SpawnRadius;

	//���� ���� ��ġ 
	UPROPERTY(EditAnyWhere, Category = SPAWN)
	TArray<AEnemySpawnPoint*> EnemySpawnPoint;

private:

	//��ǥ ���� ������
	UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  MaxAttributesGauge;
	//���� ���� ������
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  CurrentAttributesGauge;
	//������ ���� ������
	UPROPERTY(EditAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	float  AttributesGaugeNum;


	//���� ���� ����
	bool IsWaterGimbalOn;
	bool IsThunderGimbalOn;

	//��� ������ ��������
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	bool IsAllGimbalOn;

	// Timer
	FTimerHandle TimerHandle;

	//Ÿ�Ӷ��� Ŀ��
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
	//���� OnOff
	void FireGimbalOnOff();
	void WaterGimbalOnOff();
	void ThunderGimbalOnOff();

	//���� ������ ���
	void GimbalGaugeOn();

	//�� ����
	void SpawnEnemy();
};
