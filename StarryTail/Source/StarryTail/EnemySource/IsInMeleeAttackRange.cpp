// Fill out your copyright notice in the Description page of Project Settings.


#include "IsInMeleeAttackRange.h"
#include "EnemyController.h"
#include "../IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UIsInMeleeAttackRange::UIsInMeleeAttackRange()
{
	NodeName = TEXT("CanMeleeAttack");
}
bool UIsInMeleeAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyController::PlayerKey));
	if (nullptr == Player)
		return false;

	bResult = (Player->GetDistanceTo(ControllingPawn) <= AEnemyController::MeleeAttackRange);

	if (bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanMeleeAttackKey, true);
		AEnemyController::bCanMeleeAttack = true;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanMeleeAttackKey, false);
		AEnemyController::bCanMeleeAttack = false;
	}

	return bResult;
}