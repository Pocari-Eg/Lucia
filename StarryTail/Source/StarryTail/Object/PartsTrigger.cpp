// Fill out your copyright notice in the Description page of Project Settings.


#include "PartsTrigger.h"
#include "PartsObject.h"
// Sets default values
APartsTrigger::APartsTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	//초기 설정
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
}



// Called when the game starts or when spawned
void APartsTrigger::BeginPlay()
{
	Super::BeginPlay();
	//델리게이트 
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &APartsTrigger::OnBeginOverlap);

}

void APartsTrigger::TriggerOff()
{
	//트리거 충돌을 종료
	Trigger->SetGenerateOverlapEvents(false);
}

void APartsTrigger::TriggerOn()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(true);
}


void APartsTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//이 트리거가 시작 트리거 이면 시작 오브젝트의 움직임을 시작
	if (IsStartTrigger) {
		UE_LOG(LogTemp, Error, TEXT("StartTrigger Hit"));
		if (StartObject != nullptr)
		{
			StartObject->MovingStart(this);
			//시작 트리거 종료
			TriggerOff();
		}
	}
	else {
		// 이 트리거가 종료 트리거 이면 
		UE_LOG(LogTemp, Error, TEXT("EndTrigger Hit"));
		if (EndObject != nullptr)
		{
			//종료 트리거가 작동했음을 알리고 트리거 종료
			EndObject->IsEndTriggerOn = true;
			TriggerOff();
		}
	}
}