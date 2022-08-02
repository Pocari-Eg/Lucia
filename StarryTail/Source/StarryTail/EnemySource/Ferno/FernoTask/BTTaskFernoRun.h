// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include"../Ferno.h"
#include "BTTaskFernoRun.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskFernoRun : public UBTTaskNode
{
	GENERATED_BODY()
		UBTTaskFernoRun();
virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
