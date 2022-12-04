// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../Lucia.h"
#include "FBouldelithDataStruct.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BluePrintType)
struct FBouldelithDataStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AnotherMonsterStateCheckRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultBattleRunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BackstepCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BrokenAnimePlayRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float M_PlayerMaxDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Attack3_Distance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BattleDistance;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float CurrentBattleRunSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int AttackFailedStack;



};
