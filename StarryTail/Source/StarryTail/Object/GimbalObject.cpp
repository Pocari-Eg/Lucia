// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalObject.h"

// Sets default values
AGimbalObject::AGimbalObject()
{
	//�ʱ� ����
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	RootComponent = Center;
	
	
	FireGimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FIREGIMBAL"));
	WaterGimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WATERGIMBAL"));
	ThunderGimbal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("THUNDERGIMBAL"));

	FireGimbal->SetupAttachment(RootComponent);
	WaterGimbal->SetupAttachment(RootComponent);
	ThunderGimbal->SetupAttachment(RootComponent);

	FireGimbal->SetRelativeLocation(FVector::ZeroVector);
	WaterGimbal->SetRelativeLocation(FVector::ZeroVector);
	ThunderGimbal->SetRelativeLocation(FVector::ZeroVector);

	FireGimbal->SetCollisionProfileName("NoCollision");
	WaterGimbal->SetCollisionProfileName("NoCollision");
	ThunderGimbal->SetCollisionProfileName("NoCollision");

	IsFireGimbalOn = false;
	IsWaterGimbalOn = false;
	IsThunderGimbalOn = false;

	IsAllGimbalOn = false;


	MaxAttributesGauge = 100.0f;
	CurrentAttributesGauge = 0.0f;
	AttributesGaugeNum = 10.0f;

	static ConstructorHelpers::FObjectFinder<UCurveFloat>CURVE(TEXT("/Game/Developers/Pocari/Collections/Curve/PartsObjCurve.PartsObjCurve"));

	if (CURVE.Succeeded())
	{
		TimeLineCurve = CURVE.Object;
	}

	IsTimeLineOn = false;

	RotationAccel = 0.0f;
	AccelSpeed = 0.1f;
}

// Called when the game starts or when spawned
void AGimbalObject::BeginPlay()
{
	Super::BeginPlay();
	
	//���� ��������Ʈ ����
	if(FireOccupiedArea!=nullptr)
		FireOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::FireGimbalOnOff);
	if (WaterOccupiedArea != nullptr)
		WaterOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::WaterGimbalOnOff);
	if (ThungerOccupiedArea != nullptr)
		ThungerOccupiedArea->OnOccupy.AddUObject(this, &AGimbalObject::ThunderGimbalOnOff);
	

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
void AGimbalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Ÿ�Ӷ��� ���� ����
	if (IsTimeLineOn == true)GimbalTimeline.TickTimeline(DeltaTime);

	//���� �Ӽ� ������ ������ ���� ȸ��
	IsFireGimbalOn == true ? FireGimbal->AddWorldRotation(FRotator(0.0f, FireGimbalSpeed* RotationAccel, 0.0f)) : FireGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	IsWaterGimbalOn == true ? WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, WaterGimbalSpeed* RotationAccel)) : WaterGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	IsThunderGimbalOn == true ? ThunderGimbal->AddWorldRotation(FRotator(ThunderGimbalSpeed* RotationAccel, 0.0f, 0.0f)) : ThunderGimbal->AddWorldRotation(FRotator(0.0f, 0.0f, 0.0f));

}

void AGimbalObject::Acceleration()
{

	//���� ȸ�� ���� 
	float TimelineVal = GimbalTimeline.GetPlaybackPosition();
	 RotationAccel = TimeLineCurve->GetFloatValue(TimelineVal);

   
}

void AGimbalObject::AccelerationOff()
{
	//���� ȸ�� �ӵ� ����
	IsTimeLineOn = false;
	if (RotationAccel == 0.0f)
	{
		if (IsFireGimbalOn) IsFireGimbalOn = false;
		else if (IsWaterGimbalOn) IsWaterGimbalOn = false;
		else if (IsThunderGimbalOn) IsThunderGimbalOn = false;

	}
}

void AGimbalObject::GimbalGaugeOn()
{
	//��ǥ ��ġ�� �����ϸ� ��� ����
	if (CurrentAttributesGauge >= MaxAttributesGauge) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	//���� ���ϸ� ��ġ ���
	else if (CurrentAttributesGauge <= MaxAttributesGauge - AttributesGaugeNum)
	{
		CurrentAttributesGauge += AttributesGaugeNum;
	}
}

void AGimbalObject::FireGimbalOnOff()
{
	//������ ���������� 
	if (IsFireGimbalOn == false) {
		//������ Ű�� ȸ�� �ӵ� ����
		IsFireGimbalOn = true;
		IsTimeLineOn = true;
		GimbalTimeline.PlayFromStart();
		if (IsWaterGimbalOn == true && IsThunderGimbalOn == true)
		{
			//�ٸ� ������ �������� ���� ������ ���
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		//���� ����
		//ȸ�� �ӵ� ����
		IsAllGimbalOn = false;
		IsTimeLineOn = true;
		GimbalTimeline.Reverse();
		//���� ������ ��� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

//���ϵ���
void AGimbalObject::WaterGimbalOnOff()
{
	if (IsWaterGimbalOn == false) {
		IsTimeLineOn = true;
		IsWaterGimbalOn = true;
		GimbalTimeline.PlayFromStart();
		if (IsFireGimbalOn == true && IsThunderGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;
		IsTimeLineOn = true;
		GimbalTimeline.Reverse();
		GetWorldTimerManager().ClearTimer(TimerHandle);

	}
}

void AGimbalObject::ThunderGimbalOnOff()
{
	if (IsThunderGimbalOn == false) {
		IsThunderGimbalOn = true;
		IsTimeLineOn = true;

		GimbalTimeline.PlayFromStart();
		if (IsWaterGimbalOn == true && IsFireGimbalOn == true)
		{
			IsAllGimbalOn = true;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGimbalObject::GimbalGaugeOn, 1.0f, true, 0.0f);

		}
	}
	else {
		IsAllGimbalOn = false;
		IsTimeLineOn = true;
		GimbalTimeline.Reverse();
		GetWorldTimerManager().ClearTimer(TimerHandle);

	}
}




