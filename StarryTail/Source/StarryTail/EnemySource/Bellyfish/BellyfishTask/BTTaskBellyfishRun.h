// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include"../Bellyfish.h"
#include "BTTaskBellyfishRun.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskBellyfishRun : public UBTTaskNode
{
	GENERATED_BODY()
		UBTTaskBellyfishRun();
virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
