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
		float RushTime;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int FeatherCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ClawSuccessedCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttributeKeyword CurrentAttribute;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int BarrierCount;
};