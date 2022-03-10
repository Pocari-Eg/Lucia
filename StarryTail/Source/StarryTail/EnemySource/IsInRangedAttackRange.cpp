// Fill out your copyright notice in the Description page of Project Settings.


#include "IsInRangedAttackRange.h"
#include "EnemyController.h"
#include "../IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


UIsInRangedAttackRange::UIsInRangedAttackRange()
{
	//비헤이비어 트리 데코레이터 이름
	NodeName = TEXT("CanRangedAttack");
}

bool UIsInRangedAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyController::PlayerKey));
	if (nullptr == Player)
		return false;

	// 5m
	bResult = (Player->GetDistanceTo(ControllingPawn) <= AEnemyController::RangedAttackRange);

	if (bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanRangedAttackKey, true);
		AEnemyController::bCanRangedAttack = true;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanRangedAttackKey, false);
		AEnemyController::bCanRangedAttack = false;
	}

	return bResult;
}
