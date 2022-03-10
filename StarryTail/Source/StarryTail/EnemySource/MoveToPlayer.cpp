// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToPlayer.h"
#include "../Enemy.h"
#include "EnemyController.h"
#include "../IreneCharacter.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UMoveToPlayer::UMoveToPlayer()
{
	bIsArrive = false;
}
EBTNodeResult::Type UMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
		return EBTNodeResult::Failed;
	
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyController::PlayerKey));
	if (nullptr == Player)
		return EBTNodeResult::Failed;

	auto EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()->GetPawn()->GetController());
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(EnemyController, Player->GetActorLocation());

	//돌진 속도
	Enemy->GetCharacterMovement()->MaxWalkSpeed = 600.f;

	AEnemyController::RangedAttackCount = 0;

	if (Player->GetDistanceTo(Enemy) <= AEnemyController::MeleeAttackRange)
	{
		Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.f;

		//돌진 종료 후 RangedAttackCount값 초기화
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AEnemyController::RangedAttackCountKey, AEnemyController::RangedAttackCount);
		bIsArrive = true;
	}
	if (Player->GetDistanceTo(Enemy) <= AEnemyController::RangedAttackRange && AEnemyController::RangedAttackCount == 0)
	{
		Enemy->GetCharacterMovement()->MaxWalkSpeed = 300.f;

		OwnerComp.GetBlackboardComponent()->SetValueAsInt(AEnemyController::RangedAttackCountKey, AEnemyController::RangedAttackCount);
		bIsArrive = true;
	}


	return EBTNodeResult::InProgress;
}

void UMoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (bIsArrive)
	{
		bIsArrive = false;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}