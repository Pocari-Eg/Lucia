// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobMoveToPlayer.h"

#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMobMoveToPlayer::UBTTaskMobMoveToPlayer()
{
	NodeName = TEXT("MoveToPlayer");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMobMoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	FollowSeconds = 0.0f;
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	Monster->GetAIController()->MoveToLocation(Player->GetActorLocation());

	return EBTNodeResult::InProgress;
}
void UBTTaskMobMoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsCanAttackKey) == true)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Moving)
	{
		Monster->GetAIController()->MoveToLocation(Player->GetActorLocation());
	}

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsCanAttackKey) == false)
	{
		FollowSeconds += DeltaSeconds;
		if (FollowSeconds >= Monster->GetMaxFollowTime())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
			FollowSeconds = 0.0f;
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			
		}
	}



}
