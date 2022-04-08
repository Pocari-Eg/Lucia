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
		UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* BurnEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* FloodingEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* ShockEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* TransitionEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystem* AssembleEffect;

	//Rotation, Scale
	//Hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator HitEffectRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector HitEffectScale;
	//Debuff - Burn/Flooding/Shock
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator DebuffEffectRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector DebuffEffectScale;
	//Transition
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator TransitionEffectRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TransitionEffectScale;
	//Assemble
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator AssembleEffectRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector AssembleEffectScale;
};
