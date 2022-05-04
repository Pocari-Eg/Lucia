// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack3.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdAttack3::UBTTaskBdAttack3()
{
	NodeName = TEXT("Attack3");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack3::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Attack3();

	bIsAttacking = true;
	Bouldelith->Attack3End.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack3::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsAttacking)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack3Key, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}