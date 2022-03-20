// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceMbDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTServiceMbDetectPlayer : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceMbDetectPlayer();
	FVector AngleToDir(float angle);
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
