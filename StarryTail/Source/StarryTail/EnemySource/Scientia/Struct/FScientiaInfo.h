// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../../StarryTail.h"
#include "FScientiaInfo.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FScientiaInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttributeSettingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Attack2Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Attack3Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Attack4Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DodgeSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RushTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ChangeCoolTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float FireBarrier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float WaterBarrier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ThunderBarrier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DropTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Damage;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttributeKeyword CurrentAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsFireBarrierCrushed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsWaterBarrierCrushed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsThunderBarrierCrushed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int FeatherCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ClawSuccessedCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int BarrierCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float DropTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int DropCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString State;
};