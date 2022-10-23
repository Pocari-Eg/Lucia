// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskSwirl.h"
#include "../Bellarus.h"
#include "../BellarusAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskSwirl::UBTTaskSwirl()
{
	NodeName = TEXT("BasicSwirl");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskSwirl::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellarus = Cast<ABellarus>(OwnerComp.GetAIOwner()->GetPawn());

	Bellarus->SwirlAttackType = 0;
	Bellarus->PlaySwirlAnim();
	Bellarus->GetAIController()->StopMovement();
	bIsAttacking = true;
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellarus->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskSwirl::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (!bIsAttacking)
	{
	
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);

		Cast<ABellarusAIController>(Monster->GetAIController())->AllAttackOff();
		//OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);


		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}