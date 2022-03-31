// Fill out your copyright notice in the Description page of Project Settings.


//오브젝트의 상하 운동 기능은 TimeLine이 블루프린트에서 사용이 원활하여
//블루 프린트에서 구현
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h" 
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"



#include "PartsObject.generated.h"
class APartsTrigger;
UCLASS()
class STARRYTAIL_API APartsObject : public AActor
{
	GENERATED_BODY()

	public:
	//물체가 한번 이동할때 얼마나 이동할것인가.
	UPROPERTY(EditAnywhere, Category = Platform)
	float Speed;
	UPROPERTY(EditAnywhere, Category = Platform)
	USphereComponent* Center;
	//메쉬
	UPROPERTY(EditAnywhere, Category = Platform)
	UStaticMeshComponent* Mesh;
	//이동경로 Spline
	UPROPERTY(EditAnywhere, Category = Platform)
	USplineComponent* Track;

	//다음 오브젝트 
	UPROPERTY(EditAnywhere, Category = Platform)
	APartsObject* NextObject;
	//이적 오브젝트
	UPROPERTY(EditAnywhere, Category = Platform)
	APartsObject* PrevObject;

	//상하 움직임 거리
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Platform)
	float ZMovementDistance;
	//상하 움직임 속도
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Platform)
	float ZMovementSpeed;
	//상하 움직임을 할것인지
	UPROPERTY(BluePrintReadOnly, Category = Platform)
	bool ZMoving;

	//두번째 트리거가 작동되야할 시간
	UPROPERTY(EditAnywhere, Category = Event)
	int32 TriggerTime;
	//두번째 트리거 작동 여부
	UPROPERTY(EditAnywhere, Category = Event)
	bool IsEndTriggerOn;

private:

	//경로에 오브젝트를 몇초마다 이동시킬것인지
	float Time;
	//경로에 몇퍼센트 이동했는지
	float Percent;
	// Timer
	FTimerHandle TimerHandle;

	//경로 시작 위치
	FVector InitSplineLocation;
	//상하 움직임 속도 저장
	float InitZMovementSpeed;

	//트리거 재사용시 사용 제한 시간 저장
	int32 InitTriggerTime;

	APartsTrigger* PartsTrigger;

public:
	// Sets default values for this actor's properties
	APartsObject();
	virtual void Tick(float DeltaTime) override;

	//경로 정방향 움직임 작동
	void ForwardMove(APartsTrigger* Trigger);
	//경로 역방향 움직임 작동
	void BackwardMove();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//정방향 움직임
	void Forward();
	//역방향 움직임
	void Backward();
	//다음 트리거 작동 시간 측정
	void CountDown();


};
