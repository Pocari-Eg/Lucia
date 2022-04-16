// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsObject.h"
#include "PartsTrigger.h"
// Sets default values
APartsObject::APartsObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//초기값 세팅
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

	static ConstructorHelpers::FObjectFinder<UCurveFloat>CURVE(TEXT("/Game/Developers/Pocari/Collections/Curve/PartsObjCurve.PartsObjCurve"));

	if (CURVE.Succeeded())
	{
		TimeLineCurve= CURVE.Object;
	}
	ZMovementSpeed = 1.0f;
	ZMovementDistance = 1.0f;
	ZMoving = true;
	IsBackMove = false;
	IsEndTriggerOn = false;
	IsTimelineOn = false;
	IsHoverStop = false;
	AccelSpeed = 0.1f;
}

void APartsObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//틱 마다 타임 라인 호출
	if(IsTimelineOn==true)PartsObjTimeline.TickTimeline(DeltaTime);
}


// Called when the game starts or when spawned
void APartsObject::BeginPlay()
{
	Super::BeginPlay();
	//초기 설정값 저장 
	InitSplineLocation = Track->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
	InitZMovementSpeed = ZMovementSpeed;
	InitTriggerTime = TriggerTime;

	//타임라인 속도 설정
	PartsObjTimeline.SetPlayRate(AccelSpeed);

	//타임라인 시작 호출 함수
	FOnTimelineFloat TimelineCallback;
	//타임라인 종료 호출 함수
	FOnTimelineEventStatic TimelineFinishedCallback;

	//함수 바인딩 
	TimelineCallback.BindUFunction(this, FName("MovingObject"));
	TimelineFinishedCallback.BindUFunction(this, FName(TEXT("NextMoveSet")));
	PartsObjTimeline.AddInterpFloat(TimeLineCurve, TimelineCallback);
	PartsObjTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	PartsObjTimeline.SetTimelineLength(1.0f);
}

#pragma region SplineMove
void APartsObject::MovingStart(APartsTrigger* Trigger)
{
	PartsTrigger = Trigger;
	//상하 움직임을 멈춤고 타임라인 을 시작 
	ZMovementSpeed = 0.0f;
	ZMoving = false;
	IsTimelineOn = true;
	IsHoverStop = true;
	PartsObjTimeline.PlayFromStart();
}
void APartsObject::NextMoveSet()
{
	//뒤로가는 상황이 아니면
	if (IsBackMove == false)
	{
		Track->SetLocationAtSplinePoint(0, InitSplineLocation, ESplineCoordinateSpace::Local);
		if (NextObject != nullptr)
		{
			//다음 오브젝트도 움직임 
			NextObject->MovingStart(PartsTrigger);
		}
		else {
			//다음 오브젝트가 없으면 마지막 오브젝트이므로 카운트 다운
			GetWorldTimerManager().SetTimer(TimerHandle, this, &APartsObject::CountDown, 1.0f, true, 0.0f);
		}
	}
	else {
		
		IsHoverStop = false;
		ZMovementSpeed = InitZMovementSpeed;
		ZMoving = true;
		IsBackMove = false;
		//이전 오브젝트도 제자리로
		if (PrevObject != nullptr)
		{
			//이전오브젝트가 있으면 뒤로가기 on
			//타임 라인 거꾸로
			PrevObject->IsBackMove = true;
			PrevObject->PartsObjTimeline.Reverse();
		}
		else {
			//이전 오브젝트가 없으면 트리거 켜기
			//타임라인 종료
			PartsTrigger->TriggerOn();
			IsTimelineOn = false;
		}
	}
}
void APartsObject::MovingObject()
{
	//타임라인에서 x y 값을 불러옴
	float TimelineVal = PartsObjTimeline.GetPlaybackPosition();
	float CurveDistance = TimeLineCurve->GetFloatValue(TimelineVal);

	//Spline 에서 현재 총 길이에서 해당 퍼센트만큼 불러옴
	float Distance = FMath::Lerp(0.0f, Track->GetSplineLength(), CurveDistance);

	FVector NewLocation = Track->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
	FRotator NewRotation = Track->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

	Mesh->SetWorldLocation(NewLocation);
	Mesh->SetWorldRotation(NewRotation);
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
			IsBackMove = true;
			TriggerTime = InitTriggerTime;
			PartsObjTimeline.Reverse();
			
		}
	}
}
#pragma endregion