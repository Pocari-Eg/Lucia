// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../StarryTail.h"
#include "Components/ActorComponent.h"
#include "MonsterShield.generated.h"


UCLASS(ClassGroup = (Rendering, Common), hidecategories = Object, hidecategories = Physics, hidecategories = Collision, showcategories = Trigger, editinlinenew, meta = (BlueprintSpawnableComponent))

class STARRYTAIL_API UMonsterShield : public USceneComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = INFO, Meta = (AllowPrivateAccess = true))
	UCapsuleComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effect, Meta = (AllowPrivateAccess = true))
	UParticleSystemComponent* ShiledEffectComponent;


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

public:
	// Sets default values for this component's properties
	UMonsterShield();

public:
   void CalcDurability(float Damage);

	void SetOpacity(float CurDistance);

	float GetDurability() { return Durability;}

	float GetKnockBackDistance();

	bool GetShieldAcitve(){ return bIsShieldActive; }

	float GetDurabilityRatio();

	int32 GetCurShieldState() {return CurShieldState;}

	void SetEffectVisible(bool State);


	void InitShieldEffect(UParticleSystem* Effect, FVector Location, FVector Scale);
	void InitShieldCollision(float Height, float Radius);
	

private:
	float CalcShieldDamage(float Damage);

	void DestroyedShield();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
