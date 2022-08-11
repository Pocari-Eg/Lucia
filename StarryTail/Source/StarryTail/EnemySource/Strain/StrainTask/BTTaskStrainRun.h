// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include"../Strain.h"
#include "BTTaskStrainRun.generated.h"

/**
 * 
 */
UCLASS()
class STARRYTAIL_API UBTTaskStrainRun : public UBTTaskNode
{
	GENERATED_BODY()
		UBTTaskStrainRun();
virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
