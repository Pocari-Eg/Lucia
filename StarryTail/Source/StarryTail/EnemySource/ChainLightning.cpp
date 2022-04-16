// Fill out your copyright notice in the Description page of Project Settings.


#include "ChainLightning.h"
#include "../STGameInstance.h"

// Sets default values
AChainLightning::AChainLightning()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = Collision;
	Collision->InitSphereRadius(0.01f);
	Collision->SetCollisionProfileName(TEXT("ChainLightning"));

	MoveSpeed = 0.0f;
	Count = 0;
}
void AChainLightning::Init()
{
	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	for (auto& Elem : STGameInstance->GetChainMonsterList())
	{
		MoveTargetList.Add(Elem->GetActorLocation());
	}
	TargetCount = STGameInstance->GetChainMonsterList().Num();
}
void AChainLightning::SetMoveSpeed(float Value)
{
	MoveSpeed = Value;
}
void AChainLightning::SetDamage(float Value)
{
	Damage = Value;
}
float AChainLightning::GetDamage() const
{
	return Damage;
}
void AChainLightning::AddCount()
{
	Count++;

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());
	if (Count == TargetCount)
	{
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
		STGameInstance->ResetChainMonsterList();
		Destroy();
	}
}
void AChainLightning::CheckDistance()
{
	if ((GetActorLocation() - MoveTargetList[Count]).Size() < 30.0f)
		AddCount();
}
// Called when the game starts or when spawned
void AChainLightning::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChainLightning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Count == TargetCount)
		return;

	MoveDir = MoveTargetList[Count] - GetActorLocation();
	MoveDir.Normalize();

	NewLocation = GetTransform().GetLocation() + (MoveDir * MoveSpeed * DeltaTime);

	RootComponent->SetWorldLocation(NewLocation);

	CheckDistance();
}

