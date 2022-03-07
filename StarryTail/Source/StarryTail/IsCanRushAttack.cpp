// Fill out your copyright notice in the Description page of Project Settings.


#include "IsCanRushAttack.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"


UIsCanRushAttack::UIsCanRushAttack()
{
	NodeName = TEXT("CanRushAttack");
}
bool UIsCanRushAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto RangedAttackCount = OwnerComp.GetBlackboardComponent()->GetValueAsInt(AEnemyController::RangedAttackCountKey);
	
	if (RangedAttackCount < 3)
		return false;

	return true;
}