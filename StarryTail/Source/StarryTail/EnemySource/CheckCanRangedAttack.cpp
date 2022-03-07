// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckCanRangedAttack.h"
#include "../IreneCharacter.h"
#include "EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"

UCheckCanRangedAttack::UCheckCanRangedAttack()
{
	NodeName = TEXT("CheckCanRangedAttack");
	Interval = 1.0f;
}
void UCheckCanRangedAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyController::PlayerKey));
	if (nullptr == Player) return;

	bool bResult = (Player->GetDistanceTo(ControllingPawn) <= AEnemyController::RangedAttackRange);

	if (bResult)
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanRangedAttackKey, true);
	else
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanRangedAttackKey, false);
}