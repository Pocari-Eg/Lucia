// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../StarryTail.h"

#include "HeliosAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UHeliosAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	EHeliosStateEnum HeliosState;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bShield;
public:
	bool GetShield()const{return bShield;}
	
	void SetHeliosStateAnim(const EHeliosStateEnum Value) { HeliosState = Value; }
	void SetShield(const bool Value) { bShield = Value; }

};
