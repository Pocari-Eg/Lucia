// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFernoAttacked.h"
#include"../../Monster.h"
#include"../FernoAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskFernoAttacked::UBTTaskFernoAttacked()
{
	NodeName = TEXT("FernoAttacked");
	bNotifyTick = true;
	WaitTimer = 0.0f;
	WaitTime = 2.0f;
}
EBTNodeResult::Type UBTTaskFernoAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	bIsAttacked = true;
	Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	return EBTNodeResult::InProgress;
}

void UBTTaskFernoAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	WaitTimer += DeltaSeconds;
	if (!bIsAttacked)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackedKey, false);
		WaitTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	if (WaitTimer >= WaitTime)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFernoAIController::IsAttackedKey, false);
		WaitTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
