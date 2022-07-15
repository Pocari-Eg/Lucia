// Fill out your copyright notice in the Description page of Project Settings.
#include "Quill.h"

#include "StarryTail/EnemySource/Monster.h"
#include "IreneAttackInstance.h"
// Sets default values
AQuill::AQuill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

    const ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Quill(TEXT("/Engine/BasicShapes/Cone.Cone"));
	if(SM_Quill.Succeeded())
	{
		MeshComponent->SetStaticMesh(SM_Quill.Object);
	}
	MeshComponent->SetRelativeScale3D(FVector(0.3f,0.2f,0.5f));
	MeshComponent->SetCollisionProfileName(TEXT("PlayerAttack"));

	CapsuleComponent->SetupAttachment(MeshComponent);
	CapsuleComponent->SetCollisionProfileName(TEXT("PlayerAttack"));

	LifeTime = 0;
}

// Called when the game starts or when spawned
void AQuill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;

	if(Target == nullptr)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorUpVector() * MoveSpeed * DeltaTime;
		LifeTime += DeltaTime;
		SetActorLocation(NewLocation);
	}
		
	if(LifeTime >= Distance/MoveSpeed)
		Destroy();
}

void AQuill::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(Target == nullptr)
	{
		if(Cast<AMonster>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Strength, nullptr, this, nullptr);
		}
	}
	
	if(OtherActor == Target)
	{
		if(Cast<AMonster>(OtherActor))
		{
			UGameplayStatics::ApplyDamage(OtherActor, Strength, nullptr, this, nullptr);
		}
	}
}

