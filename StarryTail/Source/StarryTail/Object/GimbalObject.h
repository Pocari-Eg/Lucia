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
	//�߾� ���� ����
	UPROPERTY(EditAnyWhere)
	UStaticMeshComponent* Center;

	//���� �Ӽ� �޽�
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UStaticMeshComponent* FireGimbal;
	UPROPERTY(EditAnyWhere, Category = GIMBAL)
	UStaticMeshComponent* WaterGimbal;
	UPROPERTY(EditAnyWhere,Category=GIMBAL)
	UStaticMeshComponent* ThunderGimbal;

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
	bool IsFireGimbalOn;
	bool IsWaterGimbalOn;
	bool IsThunderGimbalOn;

	//��� ������ ��������
	UPROPERTY(VisibleAnywhere, Category = Occupied, meta = (AllowPrivateAccess = "true"))
	bool IsAllGimbalOn;

	// Timer
	FTimerHandle TimerHandle;


	//Ÿ�� ����
	
	//Ÿ�Ӷ��� Ŀ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* TimeLineCurve;
	//Ÿ�Ӷ���
	FTimeline GimbalTimeline;

	//Ÿ�Ӷ��� ����
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
	//���� OnOff
	void FireGimbalOnOff();
	void WaterGimbalOnOff();
	void ThunderGimbalOnOff();


	//���� ����
	UFUNCTION()
	void Acceleration();

	//���� ����
	UFUNCTION()
	void AccelerationOff();
	//���� ������ ���
	void GimbalGaugeOn();
};
