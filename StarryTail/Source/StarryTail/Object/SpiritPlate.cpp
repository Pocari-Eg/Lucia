// Fill out your copyright notice in the Description page of Project Settings.


#include "SpiritPlate.h"
#include "../PlayerSource/IreneCharacter.h"
#include "../PlayerSource/PlayerInstance/IreneUIManager.h"
#include "../STGameInstance.h"
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
	SpiritPlateColiision->SetCollisionProfileName("NoCollision");
	SpiritPlateColiision->SetGenerateOverlapEvents(false);

	bIsInPlayer = false;

	InitHeight = SpiritPlateColiision->GetRelativeLocation().Z;
}

void ASpiritPlate::SpiritPlateOn()
{
	STARRYLOG(Error, TEXT("Plate Effect On"));

	PlateEffectComponent->SetActive(true, true);
	SpiritPlateColiision->SetGenerateOverlapEvents(true);
	SpiritPlateColiision->SetCollisionProfileName("AOEShield");
	SpiritPlateColiision->SetRelativeLocation(FVector(SpiritPlateColiision->GetRelativeLocation().X, SpiritPlateColiision->GetRelativeLocation().Y, InitHeight));
}

void ASpiritPlate::SpiritPlateOff()
{
	STARRYLOG(Warning, TEXT("%s"),*GetName());
	STARRYLOG(Warning, TEXT("Plate Effect Off"));
	PlateEffectComponent->Deactivate();
	SpiritPlateColiision->SetRelativeLocation(FVector(SpiritPlateColiision->GetRelativeLocation().X, SpiritPlateColiision->GetRelativeLocation().Y, SpiritPlateColiision->GetRelativeLocation().Z + 3000.0f));
	SpiritPlateColiision->SetGenerateOverlapEvents(false);
	SpiritPlateColiision->SetCollisionProfileName("NoCollision");
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
	SpiritPlateColiision->SetRelativeLocation(FVector(SpiritPlateColiision->GetRelativeLocation().X, SpiritPlateColiision->GetRelativeLocation().Y, SpiritPlateColiision->GetRelativeLocation().Z + 3000.0f));

}

void ASpiritPlate::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {

		bIsInPlayer = true;
	}
}

void ASpiritPlate::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {

		bIsInPlayer = false;
		RecoveryTimer = 0.0f;
	}
}

// Called every frame
void ASpiritPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsInPlayer)
	{
		RecoveryTimer += DeltaTime;
		if (RecoveryTimer >= 1.0f)
		{
			auto Instance = Cast<USTGameInstance>(GetGameInstance());
			if (Instance != nullptr) {
				Instance->GetPlayer()->IreneUIManager->HpRecovery(SpiritRecovery_HP);
			}

			RecoveryTimer = 0.0f;
		}
	}

}

