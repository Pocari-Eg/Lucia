// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdBattleWalk.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdBattleWalk::UBTTaskBdBattleWalk()
{
	NodeName = TEXT("B_Walk");
	bNotifyTick = true;

	B_WalkTime = 5.0f;
	B_WalkTimer = 0.0f;
}
EBTNodeResult::Type UBTTaskBdBattleWalk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;


	auto BattleMonster = Cast<AMonster>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::BattleMonsterKey));
	Monster->GetAIController()->MoveToLocation(BattleMonster->GetActorLocation());


	return EBTNodeResult::InProgress;
}
void UBTTaskBdBattleWalk::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster) {
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}




	if (Monster->GetAIController()->GetMoveStatus() == EPathFollowingStatus::Moving)
	{

		auto BattleMonster = Cast<AMonster>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::BattleMonsterKey));
		if (BattleMonster != nullptr)
			Monster->GetAIController()->MoveToLocation(BattleMonster->GetActorLocation());
	}

	B_WalkTimer += DeltaSeconds;
	if (B_WalkTimer >= B_WalkTime){

		B_WalkTimer = 0.0f;
		Monster->GetAIController()->StopMovement();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}

