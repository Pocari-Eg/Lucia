// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMoveToBattleRange.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskMoveToBattleRange::UBTTaskMoveToBattleRange()
{
	NodeName = TEXT("MoveToBattleRange");
	bNotifyTick = true;


}

EBTNodeResult::Type UBTTaskMoveToBattleRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;



	Monster->PlayWalkAnim();


	return EBTNodeResult::InProgress;
}

void UBTTaskMoveToBattleRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));
	if (Monster->GetDistanceTo(Player) < Monster->GetBattleRange())
	{
		Monster->GetAIController()->SetIsInBattleRange(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else {
		Monster->MoveToPlayer(DeltaSeconds);
	}
}
