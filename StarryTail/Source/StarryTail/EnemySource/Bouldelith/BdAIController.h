// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAIController.h"
#include "BdAIController.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API ABdAIController : public AMonsterAIController
{
	GENERATED_BODY()
public:
	void Attacked();
};
