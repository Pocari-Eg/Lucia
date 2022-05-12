// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack4.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdAttack4::UBTTaskBdAttack4()
{
	NodeName = TEXT("Attack4");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack4::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Attack4();

	bIsAttacking = true;
	Bouldelith->Attack4End.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack4::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack4Key, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}