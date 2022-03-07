// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UDetectPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UDetectPlayer();

protected:
	//범위 내에 플레이어가 있는지 감지하는 함수
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
