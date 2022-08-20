// Fill out your copyright notice in the Description page of Project Settings.


#include "StageInfoTrigger.h"

#include "../../PlayerSource/PlayerInstance/IreneUIManager.h"
#include "../../PlayerSource/IreneCharacter.h"
// Sets default values
AStageInfoTrigger::AStageInfoTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
void AStageInfoTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AStageInfoTrigger::OnBeginOverlap);

}


void AStageInfoTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG_S(Error);
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {
		Irene->IreneUIManager->PlayerHud->StageNamePlay(TitleText);
		TriggerOff();
	}
}

void AStageInfoTrigger::TriggerOff()
{	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(false);
}

