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
		float e_None; //���Ӽ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_Fire; //�ҼӼ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_Water; //���Ӽ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float e_Thunder; //�����Ӽ�
};