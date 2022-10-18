// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack5.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBdAttack5::UBTTaskBdAttack5()
{
	NodeName = TEXT("Attack5");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack5::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Attack5();
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	bIsAttacking = true;
	Bouldelith->Attack1End.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack5::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
		
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::Attack5Key, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}