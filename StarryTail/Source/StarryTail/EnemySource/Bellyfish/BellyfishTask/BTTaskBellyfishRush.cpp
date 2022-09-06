// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishRush.h"
#include "../Bellyfish.h"
#include "../BellyfishAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
UBTTaskBellyfishRush::UBTTaskBellyfishRush()
{
	NodeName = TEXT("RushAttack");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTaskBellyfishRush::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);
	Bellyfish->RushAttack();

	bIsAttacking = true;
	Bellyfish->RushEnd.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}

void UBTTaskBellyfishRush::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!bIsAttacking)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
		auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr == Monster) {
		
		}
		else {
			Monster->GetAIController()->SetAttackCoolKey(true);
			Monster->SetIsAttackCool(true);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
