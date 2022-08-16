// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskMontserSetWalktoTraceAnim.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskMontserSetWalktoTraceAnim : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskMontserSetWalktoTraceAnim();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
