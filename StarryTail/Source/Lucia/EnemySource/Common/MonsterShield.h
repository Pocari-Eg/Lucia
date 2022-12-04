// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Lucia.h"
#include "Components/ActorComponent.h"
#include "MonsterShield.generated.h"


UCLASS(ClassGroup = (Rendering, Common), hidecategories = Object, hidecategories = Physics, hidecategories = Collision, showcategories = Trigger, editinlinenew, meta = (BlueprintSpawnableComponent))

class LUCIA_API UMonsterShield : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	UCapsuleComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledCrackEffectComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledHitEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = INFO, Meta = (AllowPrivateAccess = true))
	bool bIsShieldActive;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	EShieldType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float Durability;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float CurDurability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float MaxKnockBackDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float MinKnockBackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float MaxOpacityDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	float MinOpacityDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	int32 CurShieldState;

	UMaterialInstanceDynamic* ShieldMateial;


	float CrackTimer;
	float CrackTime;
	bool bIsCrackOn;
	int MaxStackCount;

	bool IsNonShield;
public:
	// Sets default values for this component's properties
	UMonsterShield();


public:
   void CalcDurability(float Damage);

	void SetOpacity(float CurDistance);

	void SetDurabilty(int DurabiltyVal) { Durability = DurabiltyVal; }
	float GetDurability() { return Durability;}

	float GetKnockBackDistance();

	bool GetShieldAcitve(){ return bIsShieldActive; }

	float GetDurabilityRatio();

	int32 GetCurShieldState() {return CurShieldState;}

	void SetEffectVisible(bool State);


	void InitShieldEffect(int M_MaxStackCount);


	
	void InitShield(bool bIsNonShield,UCapsuleComponent* ShieldCollision, UParticleSystemComponent* ShiledEffect,
		UParticleSystemComponent* ShiledCrackEffect, UParticleSystemComponent* ShiledHitEffect);
	
	void CalcStackDamageToShield(int Count);

	void ShieldRegen();

private:
	float CalcShieldDamage(float Damage);

	void DestroyedShield();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
