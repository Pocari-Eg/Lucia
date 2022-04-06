// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalPartsObject.h"


// Sets default values
AGimbalPartsObject::AGimbalPartsObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GIMBAL"));
	RootComponent = Gimbal;
	
	Gimbal->SetCollisionProfileName("NoCollision");

	IsGimbalOn = false;
	IsTimeLineOn = false;
	RotationAccel = 0.0f;

	
}

// Called when the game starts or when spawned
void AGimbalPartsObject::BeginPlay()
{
	Super::BeginPlay();
	
	//���� ��������Ʈ ����
	 

	//Ÿ�Ӷ��� �ӵ� ����
	GimbalTimeline.SetPlayRate(AccelSpeed);

	//Ÿ�Ӷ��� ���� ȣ�� �Լ�
	FOnTimelineFloat TimelineCallback;
	//Ÿ�Ӷ��� ���� ȣ�� �Լ�
	FOnTimelineEventStatic TimelineFinishedCallback;
	//�Լ� ���ε� 
	TimelineCallback.BindUFunction(this, FName("Acceleration"));
	TimelineFinishedCallback.BindUFunction(this, FName(TEXT("AccelerationOff")));
	GimbalTimeline.AddInterpFloat(TimeLineCurve, TimelineCallback);
	GimbalTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	GimbalTimeline.SetTimelineLength(1.0f);
}

// Called every frame
void AGimbalPartsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Ÿ�Ӷ��� ���� ����
	if (IsTimeLineOn == true)GimbalTimeline.TickTimeline(DeltaTime);
	////���� �Ӽ� ������ ������ ���� ȸ��
	//IsGimbalOn == true ? Gimbal->AddLocalRotation(FRotator(0.0f, GimbalSpeed * RotationAccel, 0.0f)) : Gimbal->AddLocalRotation(FRotator(0.0f, 0.0f, 0.0f));\

	if (IsGimbalOn)
	{
		switch (Attributes)
		{
		case EAttributeKeyword::e_Fire:
			Gimbal->AddWorldRotation(FRotator(0.0f, GimbalSpeed * RotationAccel, 0.0f));
			break;
		case EAttributeKeyword::e_Water:
			Gimbal->AddWorldRotation(FRotator(0.0f, 0.0f, GimbalSpeed * RotationAccel));
			break;
		case EAttributeKeyword::e_Thunder:
			Gimbal->AddWorldRotation(FRotator(GimbalSpeed * RotationAccel, 0.0f, 0.0f));
			break;
		default:
			break;
		}
	}
	else {
		Gimbal->AddLocalRotation(FRotator(0.0f, 0.0f, 0.0f));
	}
}

void AGimbalPartsObject::GimbalStart()
{
	IsGimbalOn = true;
	IsTimeLineOn = true;
	GimbalTimeline.PlayFromStart();
}

void AGimbalPartsObject::GimbalReverse()
{
	IsTimeLineOn = true;
	GimbalTimeline.Reverse();
}



void AGimbalPartsObject::Acceleration()
{
	//���� ȸ�� ���� 
	float TimelineVal = GimbalTimeline.GetPlaybackPosition();
	RotationAccel = TimeLineCurve->GetFloatValue(TimelineVal);
}

void AGimbalPartsObject::AccelerationOff()
{
	//���� ȸ�� �ӵ� ����
	IsTimeLineOn = false;
	if (RotationAccel == 0.0f)
	{
		if (IsGimbalOn) IsGimbalOn = false;

	}
}

