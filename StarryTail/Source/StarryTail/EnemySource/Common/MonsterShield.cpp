// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterShield.h"
#include "Components/CapsuleComponent.h"

#include "Particles/ParticleSystemComponent.h"
// Sets default values for this component's properties
UMonsterShield::UMonsterShield()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;




	bIsShieldActive = true;
	Durability = 500;

	MaxKnockBackDistance = 300;
	MinKnockBackDistance = 100;
	MaxOpacityDistance = 1000;
	MinOpacityDistance = 300;
	CurShieldState = 0;

	Type = EShieldType::General;

	// ...

	CrackTimer = 0.0f;
	CrackTime = 0.2f;
	bIsCrackOn = false;
}

float UMonsterShield::CalcShieldDamage(float Damage)
{
	if (Damage == -1.0f)
	{
		return 99999999.9f;
	}

	if (bIsShieldActive&&Type==EShieldType::General) {
	

		return Damage;
	}
	return 0;
}

void UMonsterShield::DestroyedShield()
{

	ShiledCrackEffectComponent->SetActive(true, true);
	SetEffectVisible(false);
	Collision->SetCollisionProfileName("NoCollision");
	bIsShieldActive = false;
}

void UMonsterShield::CalcDurability(float Damage)
{
	if (bIsShieldActive) {

		int TotalDamage = CalcShieldDamage(Damage);

		ShiledHitEffectComponent->SetActive(true, true);
		CurDurability -= TotalDamage;
		ShiledCrackEffectComponent->SetActive(true, true);


		if (CurDurability <= Durability * 0.25)
		{
			CurShieldState = 3;
			ShiledEffectComponent->InstanceParameters[1].Scalar = 1.0f;
			ShiledEffectComponent->InstanceParameters[2].Scalar = 1.0f;
			ShiledEffectComponent->InstanceParameters[3].Scalar = 1.0f;
		}
		else if (CurDurability <= (Durability * 0.5))
		{
			CurShieldState = 2;

			ShiledEffectComponent->InstanceParameters[1].Scalar = 1.0f;
			ShiledEffectComponent->InstanceParameters[2].Scalar = 1.0f;
			ShiledEffectComponent->InstanceParameters[3].Scalar = 0.0f;


		}
		else if (CurDurability <= (Durability * 0.75))
		{
			CurShieldState = 1;

			ShiledEffectComponent->InstanceParameters[1].Scalar = 1.0f;
			ShiledEffectComponent->InstanceParameters[2].Scalar = 0.0f;
			ShiledEffectComponent->InstanceParameters[3].Scalar = 0.0f;
		
		}
		else {
			CurShieldState = 0;
		}

		bIsCrackOn = true;
		CrackTimer = 0.0f;
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


void UMonsterShield::InitShieldEffect(int M_MaxStackCount)
{

	if (bIsShieldActive) {
		
		MaxStackCount = M_MaxStackCount;
		ShiledEffectComponent->SetVisibility(true);
		FParticleSysParam Opacity;
		Opacity.Name = "Opacity";
		Opacity.ParamType = PSPT_Scalar;
		Opacity.Scalar = 1.0f;

		ShiledEffectComponent->InstanceParameters.Add(Opacity);

		FParticleSysParam Crack_1;
		Crack_1.Name = "Crack_1";
		Crack_1.ParamType = PSPT_Scalar;
		Crack_1.Scalar = 0.0f;

		ShiledEffectComponent->InstanceParameters.Add(Crack_1);

		FParticleSysParam Crack_2;
		Crack_2.Name = "Crack_2";
		Crack_2.ParamType = PSPT_Scalar;
		Crack_2.Scalar = 0.0f;

		ShiledEffectComponent->InstanceParameters.Add(Crack_2);

		FParticleSysParam Crack_3;
		Crack_3.Name = "Crack_3";
		Crack_3.ParamType = PSPT_Scalar;
		Crack_3.Scalar = 0.0f;

		ShiledEffectComponent->InstanceParameters.Add(Crack_3);
	}
}



void UMonsterShield::InitShield(UCapsuleComponent* ShieldCollision, UParticleSystemComponent* ShiledEffect,
	UParticleSystemComponent* ShiledCrackEffect, UParticleSystemComponent* ShiledHitEffect)
{
	this->Collision = ShieldCollision;
	this->ShiledEffectComponent = ShiledEffect;
	this->ShiledCrackEffectComponent = ShiledCrackEffect;
	this->ShiledHitEffectComponent = ShiledHitEffect;


	this->ShiledEffectComponent->SetVisibility(false);
	

}

void UMonsterShield::CalcStackDamageToShield(int Count)
{

	const int Break_1 = MaxStackCount * 0.3;
	const int Break_2 = MaxStackCount * 0.6;
	const int Break_3 = MaxStackCount * 0.9;


	if (Count == Break_1){
		if (CurShieldState < 1)
		{
			CurShieldState = 1;
			ShiledEffectComponent->InstanceParameters[1].Scalar = 1.0f;
			ShiledEffectComponent->InstanceParameters[2].Scalar = 0.0f;
			ShiledEffectComponent->InstanceParameters[3].Scalar = 0.0f;
		}
     }  
	else if (Count == Break_2) {
			if (CurShieldState < 2)
			{
				CurShieldState = 2;
				ShiledEffectComponent->InstanceParameters[1].Scalar = 0.0f;
				ShiledEffectComponent->InstanceParameters[2].Scalar = 1.0f;
				ShiledEffectComponent->InstanceParameters[3].Scalar = 0.0f;
			}
		}
	else if (Count == Break_3) {
			if (CurShieldState < 3)
			{
				CurShieldState = 3;
				ShiledEffectComponent->InstanceParameters[1].Scalar = 0.0f;
				ShiledEffectComponent->InstanceParameters[2].Scalar = 0.0f;
				ShiledEffectComponent->InstanceParameters[3].Scalar = 1.0f;
			}
		}
}

void UMonsterShield::ShieldRegen()
{
	SetEffectVisible(true);
	bIsShieldActive = true;
	CurDurability = Durability;
	Collision->SetCollisionProfileName("Shield");

	ShiledEffectComponent->InstanceParameters[1].Scalar = 0.0f;
	ShiledEffectComponent->InstanceParameters[2].Scalar = 0.0f;
	ShiledEffectComponent->InstanceParameters[3].Scalar = 0.0f;
}

// Called when the game starts
void UMonsterShield::BeginPlay()
{
	Super::BeginPlay();

	if (Durability == 0||bIsShieldActive==false)
	{
		bIsShieldActive = false;
		Collision->SetCollisionProfileName("NoCollision");

	}
	else {
		CurDurability = Durability;
		Collision->SetCollisionProfileName("Shield");
	}
	

	// ...
}

void UMonsterShield::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bIsCrackOn)
	{
		CrackTimer += DeltaTime;
		if (CrackTimer >= CrackTime)
		{
			CrackTimer = 0.0f;
			bIsCrackOn = false;
			ShiledEffectComponent->InstanceParameters[1].Scalar = 0.0f;
			ShiledEffectComponent->InstanceParameters[2].Scalar = 0.0f;
			ShiledEffectComponent->InstanceParameters[3].Scalar = 0.0f;
		}
	}
}



