// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicStair.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMagicStair::AMagicStair()
{
	//초기 설정
	PrimaryActorTick.bCanEverTick = true;
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

void AMagicStair::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	
	if (IsActorTickEnabled() == false) {
		STARRYLOG(Error,TEXT("Tick Start"));
		SetActorTickEnabled(true);
	}
	else {
		STARRYLOG(Error, TEXT("Tick Pause"));
		SetActorTickEnabled(false);
	}
}

// Called when the game starts or when spawned
void AMagicStair::BeginPlay()
{

	Super::BeginPlay();
	SetActorTickEnabled(false);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMagicStair::OnBeginOverlap);
}

// Called every frame
void AMagicStair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = 0; i < StairArray.Num(); i++)
	{
		
	STARRYLOG(Error,TEXT("distance : %f"),StairArray[i]->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)));
	}
}

