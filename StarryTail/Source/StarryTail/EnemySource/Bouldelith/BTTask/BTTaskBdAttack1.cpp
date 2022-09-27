// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack1.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskBdAttack1::UBTTaskBdAttack1()
{
	NodeName = TEXT("Attack1");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBdAttack1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	Bouldelith->Attack1();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bouldelith->Attack1End.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
		
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		Monster->GetAIController()->OffAttack(1);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}