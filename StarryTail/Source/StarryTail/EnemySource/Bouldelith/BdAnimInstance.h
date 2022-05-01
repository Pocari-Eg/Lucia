// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MonsterAnimInstance.h"
#include "BdAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBdAnimInstance : public UMonsterAnimInstance
{
	GENERATED_BODY()
public:
	void PlayDeathMontage() override;
};
