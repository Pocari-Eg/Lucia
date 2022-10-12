// Fill out your copyright notice in the Description page of Project Settings.


#include "LabMagic.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ALabMagic::ALabMagic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AreaCheckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AREACEHCK"));
	ExplosionSignEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AttackSign_Particle"));

	AreaCheckCollision->SetupAttachment(RootComponent);
	ExplosionSignEffectComponent->SetupAttachment(RootComponent);

	ExplosionSignEffectComponent->SetAutoActivate(false);

	Explosion_Wait_Time = 10.0f;
	Explosion_SignWait_Time = 10.0f;
	Explosion_Time = 10.0f;

	bIsExplosion_Wait_Timer = false;
	Explosion_Wait_Timer = 0.0f;

	bIsExplosion_SignWait_Timer = false;
	Explosion_SignWait_Timer = 0.0f;

	bIsExplosion_Timer = false;
	Explosion_Timer = 0.0f;
	
}
void ALabMagic::StartExplosionSignWait()
{
	bIsExplosion_SignWait_Timer = true;
}

void ALabMagic::ExplosionSign()
{
	bIsExplosion_SignWait_Timer = false;
	Explosion_SignWait_Timer = 0.0f;

	ExplosionSignEffectComponent->SetActive(true, true);
	bIsExplosion_Wait_Timer = true;
}

void ALabMagic::StartExplosion()
{
	bIsExplosion_Wait_Timer = false;
	Explosion_Wait_Timer = 0.0f;
	ExplosionSignEffectComponent->SetActive(false, true);
}

void ALabMagic::Explosion()
{
}

// Called when the game starts or when spawned
void ALabMagic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALabMagic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bIsExplosion_SignWait_Timer)
	{
		Explosion_SignWait_Timer += DeltaTime;
		if (Explosion_SignWait_Timer >= Explosion_SignWait_Time) {
			ExplosionSign();
		}
	}

	if (bIsExplosion_Wait_Timer)
	{
		Explosion_Wait_Timer += DeltaTime;
		if (Explosion_Wait_Timer >= Explosion_Wait_Time) {
			StartExplosion();
		}
	}

	if (bIsExplosion_Timer)
	{
		Explosion_Timer += DeltaTime;
		if (Explosion_Timer >= Explosion_Time) {
			Explosion();
		}
	}
}

