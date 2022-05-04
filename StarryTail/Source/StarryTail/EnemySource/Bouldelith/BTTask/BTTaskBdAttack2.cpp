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

	Bouldelith->BattleRun();

	bIsNotAttacking = true;
	bIsAttacking = true;
	Bouldelith->Attack2End.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack2::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsNotAttacking)
	{
		auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
		auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABdAIController::PlayerKey));

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Bouldelith->GetController(), Player->GetActorLocation());

		if (Bouldelith->GetDistanceToPlayer() <= 300.0f)
		{
			Bouldelith->Attack2();
			bIsNotAttacking = false;
		}
	}
	if (!bIsAttacking)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack2Key, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}