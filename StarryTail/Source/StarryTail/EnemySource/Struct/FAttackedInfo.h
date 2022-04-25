// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../StarryTail.h"
#include "FAttackedInfo.generated.h"

USTRUCT(Atomic, BluePrintType)
struct FAttackedInfo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsUseMana;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Mana;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float AttributeArmor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttackedDirection AttackedDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EAttackedPower AttackedPower;
};