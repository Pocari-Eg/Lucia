// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMeleeAttack.h"
#include "EnemyController.h"
#include "../Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UEnemyMeleeAttack::UEnemyMeleeAttack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UEnemyMeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
		return EBTNodeResult::Failed;

	Enemy->MeleeAttack();

	IsAttacking = true;
	Enemy->OnAttackEnd.AddLambda([this]() -> void { IsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UEnemyMeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}