// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "../Monster.h"
#include "BTTaskMoveToSupportRange.generated.h"

/**
 * 
 */
UCLASS()
class LUCIA_API UBTTaskMoveToSupportRange : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskMoveToSupportRange();
private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool MoveToPlayerReverse(class AMonster* Monster, class AIreneCharacter* Player, float DeltaSeconds);

//	float MoveDistance;
	float CurMoveDistance;

	bool bIsOutSupportRange;
	bool bIsInBattleRange;

	float GetDistance(class AMonster* Monster, class AIreneCharacter* player);
};
