// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack2.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskBdAttack2::UBTTaskBdAttack2()
{
	NodeName = TEXT("Attack2");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack2::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Attack2();
	bIsAttacking = true;
	Bouldelith->Attack2End.AddLambda([this]() -> void { bIsAttacking = false; });
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);

	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());


	if (!bIsAttacking)
	{
	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		Monster->GetAIController()->OffAttack(2);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}