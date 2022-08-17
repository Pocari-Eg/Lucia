// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobMoveToPlayer.h"

#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../Ferno/FernoAIController.h"
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

auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	Monster->GetMonsterAnimInstance()->PlayBattleWalkMontage();
	Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));

	Monster->GetAIController()->MoveToLocation(Player->GetActorLocation());

	return EBTNodeResult::InProgress;
}
void UBTTaskMobMoveToPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Moving)
	{
		Monster->GetAIController()->MoveToLocation(Player->GetActorLocation());
	}

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsDeadKey) == true
		|| OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsAttackedKey) == true)
	{

		
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsInAttackAreaKey) == true)
	{
	
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}



	if (OwnerComp.GetBlackboardComponent()->GetValueAsBool(AMonsterAIController::IsInAttackAreaKey) == false)
	{
		FollowSeconds += DeltaSeconds;
		if (FollowSeconds >= Monster->GetMaxFollowTime())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsFindKey, false);
			FollowSeconds = 0.0f;
			Monster->GetAIController()->StopMovement();
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			
		}
	}



}
