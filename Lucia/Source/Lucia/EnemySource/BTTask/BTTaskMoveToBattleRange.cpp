// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMoveToBattleRange.h"
#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Bouldelith/Bouldelith.h"
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



	Monster->PlayBattleWalkAnim();

	if (Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		auto Random = FMath::RandRange(0, 100);
		if (Random < 40) {
			Monster->GetAIController()->OnAttack(4);
		}
	}


	return EBTNodeResult::InProgress;
}

void UBTTaskMoveToBattleRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::PlayerKey));
	if (Monster->GetDistanceTo(Player) < Monster->GetBattleRange())
	{
		Monster->GetAIController()->StopMovement();
		Monster->GetAIController()->SetIsInBattleRange(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else {
		Monster->GetAIController()->MoveTo(Player);
		//Monster->MoveToPlayer(DeltaSeconds);
	}
}
