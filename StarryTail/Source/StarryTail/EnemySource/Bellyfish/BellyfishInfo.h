// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "BellyfishInfo.generated.h"
/**
 * 
 */
USTRUCT(Atomic, BluePrintType)
struct FBellyfishInfo
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Run_Distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_Run_Time;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_MaxFlyDistance;
	//Rush
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RushSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RushTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float M_RushAtk;

	FVector AttackPosition;
	float TotalFlyDistance;
	float M_Fly_Distance;
	float DodgeTime;
};