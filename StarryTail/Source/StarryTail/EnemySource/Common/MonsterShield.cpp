// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterShield.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values for this component's properties
UMonsterShield::UMonsterShield()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SHEILD_COLLISION"));
	ShiledEffectComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SHEILD_EFFECT"));

	Collision->SetupAttachment(this);
	ShiledEffectComponent->SetupAttachment(this);



	bIsShieldActive = true;
	Durability = 500;

	MaxKnockBackDistance = 300;
	MinKnockBackDistance = 100;
	MaxOpacityDistance = 1000;
	MinOpacityDistance = 300;
	CurShieldState = 0;

	Type = EShieldType::General;

	ShiledEffectComponent->SetVisibility(false);
	// ...
}

float UMonsterShield::CalcShieldDamage(float Damage)
{
	if (bIsShieldActive) {
		return Damage;
	}
	return 0;
}

void UMonsterShield::DestroyedShield()
{
	bIsShieldActive = false;
	ShiledEffectComponent->SetVisibility(false);
}

void UMonsterShield::CalcDurability(float Damage)
{
	if (bIsShieldActive) {

	int TotalDamage=CalcShieldDamage(Damage);

	CurDurability -= TotalDamage;


	if (CurDurability <= Durability * 0.25)
	{
		CurShieldState = 3;
	}
	else if (CurDurability <= (Durability * 0.5))
	{
		CurShieldState = 2;
	}
	else if (CurDurability <= (Durability * 0.75))
	{
		CurShieldState=1;
	}
	else {
		CurShieldState=0;
	}


		if (CurDurability <= 0)
		{
			DestroyedShield();
		}

	}
}

void UMonsterShield::SetOpacity(float CurDistance)
{

	float Opacity;
	if (bIsShieldActive) {
		if (CurDistance <= MinOpacityDistance) {
			Opacity = 1.0f;
		}

		else if (CurDistance >= MaxOpacityDistance) {

			Opacity = 0.0f;
		}
		else {

			float A = CurDistance - MinOpacityDistance;
			float B = MaxOpacityDistance - MinOpacityDistance;
			Opacity = A / B;

			Opacity = 1.0f - Opacity;
		}

	
		

		ShiledEffectComponent->InstanceParameters[0].Scalar = Opacity;
		


	}


}

float UMonsterShield::GetKnockBackDistance()
{
	if (bIsShieldActive) {
		auto RandomKockBackDistance = FMath::RandRange(MinKnockBackDistance, MaxKnockBackDistance);

		return RandomKockBackDistance;
	}

	return 0.0f;
}


float UMonsterShield::GetDurabilityRatio()
{
	if (bIsShieldActive)
		return CurDurability < KINDA_SMALL_NUMBER ? 0.0f : CurDurability / Durability;

   return 0.0f;
}

void UMonsterShield::SetEffectVisible(bool State)
{
	if (bIsShieldActive)
	{
		
		ShiledEffectComponent->SetVisibility(State);
	}
}


void UMonsterShield::InitShieldEffect(UParticleSystem* Effect, FVector Location, FVector Scale)
{

	if (bIsShieldActive) {
		ShiledEffectComponent->SetRelativeScale3D(Scale);
		ShiledEffectComponent->SetRelativeLocation(Location);
		ShiledEffectComponent->SetTemplate(Effect);
		ShiledEffectComponent->SetVisibility(true);
		FParticleSysParam Param;
		Param.Name = "Opacity";
		Param.ParamType = PSPT_Scalar;
		Param.Scalar = 1.0f;

		ShiledEffectComponent->InstanceParameters.Add(Param);
	}
}

// Called when the game starts
void UMonsterShield::BeginPlay()
{
	Super::BeginPlay();
	CurDurability = Durability;
	// ...


	
}



