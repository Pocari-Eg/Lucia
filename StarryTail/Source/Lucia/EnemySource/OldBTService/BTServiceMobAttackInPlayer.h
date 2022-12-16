// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Components/LineBatchComponent.h"
#include "BTServiceMobAttackInPlayer.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTServiceMobAttackInPlayer : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceMobAttackInPlayer();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};


