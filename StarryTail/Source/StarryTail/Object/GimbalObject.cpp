// Fill out your copyright notice in the Description page of Project Settings.


#include "GimbalObject.h"

// Sets default values
AGimbalObject::AGimbalObject()
{
	//�ʱ� ����
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Center = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CENTER"));
	
	RootComponent = Center;

	ChildFireGimbal = CreateDefaultSubobject<UChildActorComponent>(TEXT("FIREGIMBAL"));
	ChildWaterGimbal = CreateDefaultSubobject<UChildActorComponent>(TEXT("WATERGIMBAL"));
	ChildThunderGimbal = CreateDefaultSubobject<UChildActorComponent>(TEXT("THUNDERGIMBAL"));

	ChildFireGimbal->SetChildActorClass(AGimbalPartsObject::StaticClass());
	ChildWaterGimbal->SetChildActorClass(AGimbalPartsObject::StaticClass());
	ChildThunderGimbal->SetChildActorClass(AGimbalPartsObject::StaticClass());

	ChildFireGimbal->SetupAttachment(RootComponent);
	ChildWaterGimbal->SetupAttachment(RootComponent);
	ChildThunderGimbal->SetupAttachment(RootComponent);

	ChildFireGimbal->SetRelativeLocation(FVector::ZeroVector);
	ChildWaterGimbal->SetRelativeLocation(FVector::ZeroVector);
	ChildThunderGimbal->SetRelativeLocation(FVector::ZeroVector);

	static ConstructorHelpers::FObjectFinder<UCurveFloat>CURVE(TEXT("/Game/Developers/Pocari/Collections/Curve/GimbalObjCurve.GimbalObjCurve"));
	if (CURVE.Succeeded())
	{
		TimeLineCurve = CURVE.Object;
	}

	MaxAttributesGauge = 100.0f;
	CurrentAttributesGauge = 0.0f;
	AttributesGaugeNum = 10.0f;
	IsAllGimbalOn = false;
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


}

void AGimbalObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	FireGimbal = Cast<AGimbalPartsObject>(ChildFireGimbal->GetChildActor());
	FireGimbal->Gimbal->SetStaticMesh(FireGimbalMesh);
	FireGimbal->GimbalSpeed = FireGimbalSpeed;
	FireGimbal->AccelSpeed = AccelSpeed;
	FireGimbal->TimeLineCurve = TimeLineCurve;
	FireGimbal->Attributes = EAttributeKeyword::e_Fire;

	WaterGimbal = Cast<AGimbalPartsObject>(ChildWaterGimbal->GetChildActor());
	WaterGimbal->Gimbal->SetStaticMesh(WaterGimbalMesh);
	WaterGimbal->GimbalSpeed = WaterGimbalSpeed;
	WaterGimbal->AccelSpeed = AccelSpeed;
	WaterGimbal->TimeLineCurve = TimeLineCurve;
	WaterGimbal->Attributes = EAttributeKeyword::e_Water;

	ThunderGimbal = Cast<AGimbalPartsObject>(ChildThunderGimbal->GetChildActor());
	ThunderGimbal->Gimbal->SetStaticMesh(ThunderGimbalMesh);
	ThunderGimbal->GimbalSpeed = ThunderGimbalSpeed;
	ThunderGimbal->AccelSpeed = AccelSpeed;
	ThunderGimbal->TimeLineCurve = TimeLineCurve;
	ThunderGimbal->Attributes = EAttributeKeyword::e_Thunder;
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
	if (FireGimbal->IsGimbalOn == false) {
		//������ Ű�� ȸ�� �ӵ� ����
		
		FireGimbal->GimbalStart();
		if (WaterGimbal->IsGimbalOn == true && ThunderGimbal->IsGimbalOn == true)
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
		FireGimbal->GimbalReverse();
		//���� ������ ��� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

//���ϵ���
void AGimbalObject::WaterGimbalOnOff()
{
	//������ ���������� 
	if (WaterGimbal->IsGimbalOn == false) {
		//������ Ű�� ȸ�� �ӵ� ����

		WaterGimbal->GimbalStart();
		if (FireGimbal->IsGimbalOn == true && ThunderGimbal->IsGimbalOn == true)
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
		WaterGimbal->GimbalReverse();
		//���� ������ ��� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void AGimbalObject::ThunderGimbalOnOff()
{
	//������ ���������� 
	if (ThunderGimbal->IsGimbalOn == false) {
		//������ Ű�� ȸ�� �ӵ� ����

		ThunderGimbal->GimbalStart();
		if (WaterGimbal->IsGimbalOn == true && FireGimbal->IsGimbalOn == true)
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
		ThunderGimbal->GimbalReverse();
		//���� ������ ��� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}




