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

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bouldelith)
		return EBTNodeResult::Failed;


	WalkPoint = Bouldelith->GetAIController()->GetBlackboardComponent()->GetValueAsVector(ABdAIController::IsWalkPointKey);

	WalkPoint.Z = Bouldelith->GetActorLocation().Z;


	bIsReturn = true;
	bIsIdle = false;
	bIsWalk = false;
	bIsSpawn = false;

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
			Timer = 0.0f;
			Monster->PlayWalkAnim();

			if (!bIsSpawn)
			{
				Monster->GetAIController()->MoveToLocation(Monster->GetAIController()->GetBlackboardComponent()->GetValueAsVector(Monster->GetAIController()->SpawnPosKey));
				bIsSpawn = true;
				bIsWalk = false;
			}
			else {
				Monster->GetAIController()->MoveToLocation(WalkPoint);
				bIsSpawn = false;
				bIsWalk = true;

			}
		
		}
		return;
	}

	if (bIsSpawn) {
		if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Idle)
		{
			Monster->GetAIController()->StopMovement();
			Monster->PlayIdleAnim();
			bIsIdle = true;
		}
	}

	else if (bIsWalk)
	{
		if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Idle)
		{
			Monster->GetAIController()->StopMovement();
			Monster->PlayIdleAnim();
			bIsIdle = true;
		}
	}
	
}
