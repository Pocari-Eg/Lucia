// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRangedAttack.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemyRangedAttack::UEnemyRangedAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UEnemyRangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
		return EBTNodeResult::Failed;

	Enemy->RangedAttack();

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(AEnemyController::RangedAttackCountKey, AEnemyController::RangedAttackCount);

	IsAttacking = true;
	Enemy->OnAttackEnd.AddLambda([this]() -> void { IsAttacking = false; });

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AEnemyController::CanRangedAttackKey, false);

	return EBTNodeResult::InProgress;
}

void UEnemyRangedAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

