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

	Bouldelith->BattleRun();

	bIsNotAttacking = true;
	bIsAttacking = true;
	Bouldelith->Attack1End.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskBdAttack1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (bIsNotAttacking)
	{
		auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
		auto Player = Cast<AIreneCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABdAIController::PlayerKey));

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(Bouldelith->GetController(), Player->GetActorLocation());

		if (Bouldelith->GetDistanceToPlayer() <= 300.0f)
		{
			Bouldelith->Attack1();
			bIsNotAttacking = false;
		}
	}
	if (!bIsAttacking)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsAttack1Key, false);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABdAIController::IsBattleIdleKey, true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}