// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskWalkState.h"
#include "../MonsterAIController.h"

#include"../Bellyfish/Bellyfish.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskWalkState::UBTTaskWalkState()
{
    NodeName = TEXT("WALKSTATE");


	WalkTimer = 0.0f;
	 WalkTime = 15.0f;

	 WaitTimer=0.0f;
	 WaitTime=2.0f;
	 bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskWalkState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	FindPatrolPos(Monster);

	Monster->GetAIController()->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::PatrolPosKey));


	return EBTNodeResult::InProgress;
}

void UBTTaskWalkState::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {

		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}



	WalkTimer += DeltaSeconds;
	if (WalkTimer >= WalkTime)
	{
		WalkTimer = 0.0f;
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
	if (Wait)
	{
		WaitTimer += DeltaSeconds;
		if (WaitTimer >= WaitTime)
		{
			WaitTimer = 0.0f;
			FindPatrolPos(Monster);
			Monster->GetAIController()->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::PatrolPosKey));
			Monster->PlayWalkAnim();
			Wait = false;
		}
		return;
	}

    if (Monster->GetAIController()->GetMoveStatus() != EPathFollowingStatus::Moving)
	{
		Monster->GetAIController()->StopMovement();
		Wait = true;
		Monster->PlayIdleAnim();
	}

}

void UBTTaskWalkState::FindPatrolPos(AMonster* Monster)
{

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Monster->GetWorld());
	if (nullptr == NavSystem)
		return;

	FVector Origin = Monster->GetAIController()->GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::SpawnPosKey);
	FNavLocation NextPatrol;

	// Orgin을 중심점으로 반지름이 600인 원 안에서 랜덤 좌표 생성
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, Monster->GetPatrolArea(), NextPatrol))
	{
		float MoveRange = FMath::RandRange(4.0f, 6.0f);
		// 좌표로 향하는 방향 벡터를 구하고
		FVector MoveDirection = NextPatrol.Location - Monster->GetTransform().GetLocation();
		// 방향 벡터로 5m 떨어진 위치
		FVector PatrolPos = FVector(Monster->GetTransform().GetLocation().X + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f).X
			, Monster->GetTransform().GetLocation().Y + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f).Y,
			Monster->GetTransform().GetLocation().Z
			);


		// 구해진 위치를 저장
		Monster->GetAIController()->GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::PatrolPosKey, NextPatrol.Location);
	}
}
