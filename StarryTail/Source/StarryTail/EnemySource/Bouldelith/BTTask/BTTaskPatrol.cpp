// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskPatrol.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskPatrol::UBTTaskPatrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;

	Time = 3.0f;
	Timer = 0.0f;
}

EBTNodeResult::Type UBTTaskPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;


	Monster->GetAIController()->MoveToLocation(Monster->GetAIController()->
		GetBlackboardComponent()->GetValueAsVector(Monster->GetAIController()->SpawnPosKey));

	bIsReturn = true;
	bIsIdle = false;
	bIsWalk = false;

	return EBTNodeResult::InProgress;
}

void UBTTaskPatrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (bIsReturn)
	{
		if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Moving)
		{
			Timer += DeltaSeconds;
			if (Timer >= Time)
			{
				Monster->GetAIController()->StopMovement();
				Monster->PlayIdleAnim();
				bIsReturn = false;
				bIsIdle = true;
				Timer = 0.0f;
			}
		} 
		else if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Idle)
		{

			Monster->GetAIController()->StopMovement();
			Monster->PlayIdleAnim();
			bIsReturn = false;
			bIsIdle = true;
			Timer = 0.0f;
		}

	}
	else if (bIsIdle)
	{
		Timer += DeltaSeconds;
		if (Timer >= Time)
		{
			bIsIdle = false;
			bIsWalk = true;
			Timer = 0.0f;
			Monster->PlayWalkAnim();
			FindPatrolPos(Monster);
			Monster->GetAIController()->MoveToLocation(Monster->GetAIController()->GetBlackboardComponent()->GetValueAsVector(Monster->GetAIController()->PatrolPosKey));
		}
	}
	else if (bIsWalk)
	{
		if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Idle)
		{
			Monster->GetAIController()->StopMovement();
			Monster->PlayIdleAnim();
			bIsIdle = true;
			bIsWalk = false;
		}
	}
	
}

void UBTTaskPatrol::FindPatrolPos(AMonster* Monster)
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Monster->GetWorld());
	if (nullptr == NavSystem)
		return;

	FVector Origin = Monster->GetAIController()->GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::SpawnPosKey);
	FNavLocation NextPatrol;

	// Orgin을 중심점으로 반지름이 600인 원 안에서 랜덤 좌표 생성
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, Monster->GetPatrolArea(), NextPatrol))
	{
		float MoveRange = FMath::RandRange((Monster->GetPatrolArea() / 100)-2.0f, Monster->GetPatrolArea() / 100.0f);
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
