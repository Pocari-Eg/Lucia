// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMonsterSetTraceAnim.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMonsterSetTraceAnim : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMonsterSetTraceAnim();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
