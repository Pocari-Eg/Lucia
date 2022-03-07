// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyRushAttack.h"
#include "EnemyController.h"
#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemyRushAttack::UEnemyRushAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UEnemyRushAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
		return EBTNodeResult::Failed;

	Enemy->RushAttack();

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(AEnemyController::RangedAttackCountKey, AEnemyController::RangedAttackCount);

	IsAttacking = true;
	Enemy->OnAttackEnd.AddLambda([this]() -> void { IsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UEnemyRushAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
