// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IreneCharacter.h"

#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	AIreneCharacter* C;

	UMyAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

		// °ø°Ý È½¼ö
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 AttackCount;
};
