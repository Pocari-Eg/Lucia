// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldSpirit.h"
#include "../Math.h"

// Sets default values
AShieldSpirit::AShieldSpirit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	Mesh->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	Mesh->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));
	const ConstructorHelpers::FObjectFinder<USkeletalMesh>PetStatic(TEXT("/Game/Animation/Irene/Helios/PC_s_idle.PC_s_idle"));
	if (PetStatic.Succeeded())
		Mesh->SetSkeletalMesh(PetStatic.Object);
}

// Called when the game starts or when spawned
void AShieldSpirit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShieldSpirit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsPetMove)
	{
		MoveToPlate(DeltaTime);
	}
}

void AShieldSpirit::SetSpiritPlate(ASpiritPlate* Target)
{
	TargetPlate = Target;
	bIsPetMove = true;
}

void AShieldSpirit::MoveToPlate(float DeltaTime)
{


	FVector ForwardVec = GetActorForwardVector();

	ForwardVec = ForwardVec.RotateAngleAxis(90.0f, GetActorUpVector());

	ForwardVec.Normalize();
	SetActorLocation(GetActorLocation() + (ForwardVec * 300 * DeltaTime));



	FVector TargetVec = TargetPlate->GetActorLocation() + FVector(0,0,100) - GetActorLocation();
	TargetVec.Normalize();


	FQuat RotationQuat = Math::VectorA2BRotation(ForwardVec, TargetVec);
    AddActorWorldRotation(RotationQuat * 0.005f);
	SetActorRotation(FRotator(0.0f, GetActorRotation().Yaw, GetActorRotation().Roll));
	


	if (FVector::Dist(TargetPlate->GetActorLocation()+FVector(0,0,100), GetActorLocation()) <= 10.0f)
	{
		bIsPetMove = false;
		TargetPlate->SpiritPlateOn();
		Destroy();
	}
}
