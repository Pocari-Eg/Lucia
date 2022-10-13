// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiritPlate.h"
#include "../PlayerSource/IreneCharacter.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ASpiritPlate::ASpiritPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	SpiritPlateColiision= CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	PlateEffectComponent= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	SpiritPlateColiision->SetupAttachment(RootComponent);
	PlateEffectComponent->SetupAttachment(RootComponent);

	PlateEffectComponent->SetAutoActivate(false);
	SpiritPlateColiision->SetCollisionProfileName("Trigger");
	SpiritPlateColiision->SetGenerateOverlapEvents(false);
}

void ASpiritPlate::SpiritPlateOn()
{
	PlateEffectComponent->SetActive(true, true);
	SpiritPlateColiision->SetGenerateOverlapEvents(true);
}

void ASpiritPlate::SpiritPlateOff()
{
	PlateEffectComponent->SetActive(false, true);
	SpiritPlateColiision->SetGenerateOverlapEvents(false);
}

void ASpiritPlate::InitSpiritPlate(float HP, float Gauge)
{
	SpiritRecovery_HP = HP;
	SpiritRecovery_Gauge = Gauge;
}

// Called when the game starts or when spawned
void ASpiritPlate::BeginPlay()
{
	Super::BeginPlay();
	SpiritPlateColiision->OnComponentBeginOverlap.AddDynamic(this, &ASpiritPlate::OnBeginOverlap);
	SpiritPlateColiision->OnComponentEndOverlap.AddDynamic(this, &ASpiritPlate::OnEndOverlap);

}

void ASpiritPlate::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {
	
		STARRYLOG_S(Error);
		Irene->IreneData.IsInvincibility = true;
		Irene->IreneData.IsSkipMonsterAttack = true;
	}
}

void ASpiritPlate::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {
		STARRYLOG_S(Error);

		Irene->IreneData.IsInvincibility = false;
		Irene->IreneData.IsSkipMonsterAttack = false;

	}
}

// Called every frame
void ASpiritPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

