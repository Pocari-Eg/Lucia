// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsObject.h"
#include "PartsTrigger.h"
// Sets default values
APartsObject::APartsObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//초기 세팅
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
	//초기 설정값 저장 
	InitSplineLocation = Track->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	InitZMovementSpeed = ZMovementSpeed;
	InitTriggerTime = TriggerTime;
}

#pragma region SplineMove
void APartsObject::ForwardMove(APartsTrigger* Trigger)
{
	PartsTrigger = Trigger;
	//상하 움직임을 멈춤
	ZMovementSpeed = 0.0f;
	ZMoving = false;
	//경로에 따라 Time 초마다 이동 
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::Forward, Time, true, 0.0f);
}

void APartsObject::BackwardMove()
{
	//경로에 따라 Time 초마다 이동 
	GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::Backward, Time, true, 0.0f);
}
void APartsObject::Forward()
{
	//경로에 100% 도달하지 못했으면
	if (Percent < 1.0f) {
		// 스피드만큼 퍼센트 추가 
		//실제로는 1.0 보다 작은 값이므로 에디터에서는 0 이상의 숫자를 표기하고 내부에서는 줄여서 사용
		float speed = Speed / 10000.0f;
		Percent += speed;

		//경로에 길이에서 Percent만큼 움직인 거리를 측정
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		// 경로에 서 Distance만큼 이동한 좌표와 회전을 받아옴.
		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

		//새 좌표와 회전 적용
		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		//초당 실행 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
		//최종에 도달했으므로 percent를 1.0으로 세팅
		Percent = 1.0f;

		//경로의 첫번째 초기위치 설정
		Track->SetLocationAtSplinePoint(0, InitSplineLocation, ESplineCoordinateSpace::Local);
		//다음 오브젝트가 있다면 다음오브젝트도 움직임
		if (NextObject != nullptr)
		{
			NextObject->ForwardMove(PartsTrigger);
		}
		else {
			//없다면 트리거 발동 카운트 다운 시작
			GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::CountDown, 1.0f, true, 0.0f);
		}
	}
}

void APartsObject::Backward()
{
	//Forward 와 형태는 같고 역방향 으로 이동.
	if (Percent > 0.0f) {
		float speed = Speed / 10000.0f;
		Percent -= speed;
		float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), Percent);

		FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
		FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

		Mesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);
	}
	else {
		//오브젝트가 제자리에 왓으면
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Percent = 0.0f;
		//상하 움직임 작동
		ZMovementSpeed = InitZMovementSpeed;
		ZMoving = true;

		//이전 오브젝트도 제자리로
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
	//두번쨰 트리거가 작동했으면
	if (IsEndTriggerOn == true)
	{
		//카운트 다운 종료
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
	else {
		//카운트 다운후 
		if (TriggerTime > 0)
		{
			TriggerTime--;
		}
		else {
			//시간이 끝나면 오브젝트를 제자리로
			GetWorldTimerManager().ClearTimer(TimerHandle);
			BackwardMove();
		}
	}
}
#pragma endregion