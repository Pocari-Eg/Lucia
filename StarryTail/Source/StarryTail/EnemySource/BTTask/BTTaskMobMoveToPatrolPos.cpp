// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobMoveToPatrolPos.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMobMoveToPatrolPos::UBTTaskMobMoveToPatrolPos()
{
	NodeName = TEXT("MoveToPatrol");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskMobMoveToPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetAIController()->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMonsterAIController::PatrolPosKey));


	return EBTNodeResult::InProgress;
}

void UBTTaskMobMoveToPatrolPos::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Idle || OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsFindKey) == true)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	
}
