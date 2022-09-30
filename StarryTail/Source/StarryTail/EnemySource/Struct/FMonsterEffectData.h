// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FMonsterEffectData.generated.h"
/**
 * 
 */
USTRUCT(Atomic, BluePrintType)
struct FMonsterEffectData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* FireHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* WaterHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* ThunderHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* NoneHitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* GroggyEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 UParticleSystem* ShieldEffect;

	//Rotation, Scale
	//Hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator HitEffectRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector HitEffectScale;

	
	//Groggy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator GroggyEffectRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector GroggyEffectScale;
};
