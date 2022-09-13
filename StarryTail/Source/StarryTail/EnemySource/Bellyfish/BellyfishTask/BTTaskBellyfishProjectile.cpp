// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishProjectile.h"

UBTTaskBellyfishProjectile::UBTTaskBellyfishProjectile()
{
	NodeName = TEXT("Attack2");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskBellyfishProjectile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bellyfish)
		return EBTNodeResult::Failed;


	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);


	Bellyfish->PlayFireAnim();

	bIsAttacking = true;
	Bellyfish->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}

void UBTTaskBellyfishProjectile::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	if (!bIsAttacking)
	{

		auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
		if (nullptr == Monster) {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}


		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
		Monster->GetAIController()->SetAttackCoolKey(true);
		Monster->SetIsAttackCool(true);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	}
}
