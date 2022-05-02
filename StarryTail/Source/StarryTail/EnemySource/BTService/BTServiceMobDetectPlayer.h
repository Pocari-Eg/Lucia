// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceMobDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTServiceMobDetectPlayer : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceMobDetectPlayer();
	FVector AngleToDir(float angle);
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
