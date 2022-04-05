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
	// �޽�
	UStaticMeshComponent* Gimbal;
	//ȸ�� �ӵ�
	float GimbalSpeed;
	//���� �ӵ�
	float AccelSpeed;
	//���� ���� ����
	bool IsGimbalOn;

	//Ÿ�Ӷ��� Ŀ��
	UCurveFloat* TimeLineCurve;

	//Ÿ�Ӷ���
	FTimeline GimbalTimeline;

	//Ÿ�Ӷ��� ����
	bool IsTimeLineOn;

	float RotationAccel;

	EAttributeKeyword Attributes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//���� Start Reverse
	void GimbalStart();
	void GimbalReverse();
private :
	
		//���� ����
	UFUNCTION()
		void Acceleration();

	//���� ����
	UFUNCTION()
		void AccelerationOff();

};
