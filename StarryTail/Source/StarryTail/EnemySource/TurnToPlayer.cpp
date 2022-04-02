// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnToPlayer.h"
#include "EnemyController.h"
#include "../IreneCharacter.h"
#include "../Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UTurnToPlayer::UTurnToPlayer()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UTurnToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Enemy)
		return EBTNodeResult::Failed;

	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyController::PlayerKey));
	if (nullptr == Player)
		return EBTNodeResult::Failed;

	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(Enemy->GetActorLocation(), Player->GetActorLocation());

	Enemy->SetActorRotation(FMath::RInterpTo(Enemy->GetActorRotation(), Rotator, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}

