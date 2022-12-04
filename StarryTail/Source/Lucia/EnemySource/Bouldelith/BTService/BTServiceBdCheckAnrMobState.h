// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTServiceBdCheckAnrMobState.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTServiceBdCheckAnrMobState : public UBTService
{
	GENERATED_BODY()
public:
	UBTServiceBdCheckAnrMobState();
protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
