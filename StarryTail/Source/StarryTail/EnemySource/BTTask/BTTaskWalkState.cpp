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

	// Orgin�� �߽������� �������� 600�� �� �ȿ��� ���� ��ǥ ����
	if (NavSystem->GetRandomPointInNavigableRadius(Origin, Monster->GetPatrolArea(), NextPatrol))
	{
		float MoveRange = FMath::RandRange(4.0f, 6.0f);
		// ��ǥ�� ���ϴ� ���� ���͸� ���ϰ�
		FVector MoveDirection = NextPatrol.Location - Monster->GetTransform().GetLocation();
		// ���� ���ͷ� 5m ������ ��ġ
		FVector PatrolPos = FVector(Monster->GetTransform().GetLocation().X + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f).X
			, Monster->GetTransform().GetLocation().Y + (MoveDirection.GetSafeNormal() * MoveRange * 100.0f).Y,
			Monster->GetTransform().GetLocation().Z
			);


		// ������ ��ġ�� ����
		Monster->GetAIController()->GetBlackboardComponent()->SetValueAsVector(AMonsterAIController::PatrolPosKey, NextPatrol.Location);
	}
}
