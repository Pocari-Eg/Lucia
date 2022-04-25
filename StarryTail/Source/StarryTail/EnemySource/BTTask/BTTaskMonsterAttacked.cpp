// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterAttacked.h"
#include "../Monster.h"
#include "../MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMonsterAttacked::UBTTaskMonsterAttacked()
{
	NodeName = TEXT("Attacked");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMonsterAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);

	bIsAttacked = true;
	Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskMonsterAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacked)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackedKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}