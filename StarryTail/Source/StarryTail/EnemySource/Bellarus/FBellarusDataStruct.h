// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FBellarusDataStruct.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BluePrintType)
struct FBellarusDataStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Swirl_MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Swirl_Pull_Force;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Swirl_DOT_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Swirl_Explosion_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Swirl_Explosion_Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Tornado_DOT_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float	Tornado_Pull_Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float M_NShield_Time;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FirstJudgeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondJudgeRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CalibrationRadius;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileOffest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OutSpawnRadiusTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttacekdTeleportTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float B_CheckTime;
};
