// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsObject.h"
#include "PartsTrigger.h"
// Sets default values
APartsObject::APartsObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//�ʱ� ����
	Track = CreateDefaultSubobject<USplineComponent>(TEXT("TRACK"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	RootComponent = Track;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);

	Percent = 0.0f;
	Time = 0.016;

	ZMovementSpeed = 1.0f;
	ZMovementDistance = 1.0f;


	ZMoving = true;


	IsEndTriggerOn = false;
}

void APartsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called when the game starts or when spawned
void APartsObject::BeginPlay()
{
	Super::BeginPlay();
	//�ʱ� ������ ���� 
	InitSplineLocation = Track->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	InitZMovementSpeed = ZMovementSpeed;
	InitTriggerTime = TriggerTime;
}

#pragma region SplineMove
void APartsObject::ForwardMove(APartsTrigger* Trigger)
{
	PartsTrigger = Trigger;
	//���� �������� ����
	ZMovementSpeed = 0.0f;
	ZMoving = false;
	//��ο� ���� Time �ʸ��� �̵� 
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::Forward, Time, true, 0.0f);
}

void APartsObject::BackwardMove()
{
	//��ο� ���� Time �ʸ��� �̵� 
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::Backward, Time, true, 0.0f);
}
void APartsObject::Forward()
{
	//��ο� 100% �������� ��������
	if (Percent < 1.0f) {
		// ���ǵ常ŭ �ۼ�Ʈ �߰� 
		//�����δ� 1.0 ���� ���� ���̹Ƿ� �����Ϳ����� 0 �̻��� ���ڸ� ǥ���ϰ� ���ο����� �ٿ��� ���
		float speed = Speed / 10000.0f;
		Percent += speed;

		//��ο� ���̿��� Percent��ŭ ������ �Ÿ��� ����
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		// ��ο� �� Distance��ŭ �̵��� ��ǥ�� ȸ���� �޾ƿ�.
		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

		//�� ��ǥ�� ȸ�� ����
		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		//�ʴ� ���� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
		//������ ���������Ƿ� percent�� 1.0���� ����
		Percent = 1.0f;

		//����� ù��° �ʱ���ġ ����
		Track->SetLocationAtSplinePoint(0, InitSplineLocation, ESplineCoordinateSpace::Local);
		//���� ������Ʈ�� �ִٸ� ����������Ʈ�� ������
		if (NextObject != nullptr)
		{
			NextObject->ForwardMove(PartsTrigger);
		}
		else {
			//���ٸ� Ʈ���� �ߵ� ī��Ʈ �ٿ� ����
			GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::CountDown, 1.0f, true, 0.0f);
		}
	}
}

void APartsObject::Backward()
{
	//Forward �� ���´� ���� ������ ���� �̵�.
	if (Percent > 0.0f) {
		float speed = Speed / 10000.0f;
		Percent -= speed;
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		//������Ʈ�� ���ڸ��� ������
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Percent = 0.0f;
		//���� ������ �۵�
		ZMovementSpeed = InitZMovementSpeed;
		ZMoving = true;

		//���� ������Ʈ�� ���ڸ���
		if (PrevObject != nullptr)
		{
			PrevObject->BackwardMove();
		}
		else {
			PartsTrigger->TriggerOn();
		}

	}
}

#pragma endregion


#pragma region Event
void APartsObject::CountDown()
{
	//�ι��� Ʈ���Ű� �۵�������
	if (IsEndTriggerOn == true)
	{
		//ī��Ʈ �ٿ� ����
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	else {
		//ī��Ʈ �ٿ��� 
		if (TriggerTime > 0)
		{
			TriggerTime--;
		}
		else {
			//�ð��� ������ ������Ʈ�� ���ڸ���
			GetWorldTimerManager().ClearTimer(TimerHandle);
			BackwardMove();
		}
	}
}
#pragma endregion