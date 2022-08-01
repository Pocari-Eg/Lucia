// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMbAttacked.h"
#include "../../Monster.h"
#include "../MbAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMbAttacked::UBTTaskMbAttacked()
{
	NodeName = TEXT("MbAttacked");
	bNotifyTick = true;
	WaitTimer = 0.0f;
	WaitTime = 2.0f;
}
EBTNodeResult::Type UBTTaskMbAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	bIsAttacked = true;

	Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskMbAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMbAIController::IsAttackedKey, false);
		WaitTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

}