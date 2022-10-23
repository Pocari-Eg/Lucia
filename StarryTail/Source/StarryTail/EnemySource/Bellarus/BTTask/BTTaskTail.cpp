// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskTail.h"
#include "../Bellarus.h"
#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskTail::UBTTaskTail()
{
	NodeName = TEXT("TAILATTACK");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskTail::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	Bellarus->PlayTailAnim();
	Bellarus->GetAIController()->StopMovement();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellarus->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskTail::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);

		Cast<ABellarusAIController>(Monster->GetAIController())->AllAttackOff();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellarusAIController::CheckKey, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}