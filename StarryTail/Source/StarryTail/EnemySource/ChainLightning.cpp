// Fill out your copyright notice in the Description page of Project Settings.


#include "ChainLightning.h"
#include "../STGameInstance.h"

// Sets default values
AChainLightning::AChainLightning()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	auto STGameInstance = Cast<USTGameInstance>(GetGameInstance());

	for (auto& Elem : STGameInstance->GetChainMonsterList())
	{
		MoveTargetList.Add(Elem->GetActorLocation());
	}
	TargetCount = MoveTargetList.Num();
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


}

