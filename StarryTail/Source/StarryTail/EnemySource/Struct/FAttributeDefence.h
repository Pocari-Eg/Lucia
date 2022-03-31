// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FAttributeDefence.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FAttributeDefence
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_None; //公加己
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_Fire; //阂加己
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_Water; //拱加己
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_Thunder; //锅俺加己
};