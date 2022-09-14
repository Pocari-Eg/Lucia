// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobAttack.h"

#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../Bellyfish/BellyfishAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTaskMobAttack::UBTTaskMobAttack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskMobAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;

	auto MonaterAnimInstance = Monster->GetMonsterAnimInstance();
	if (MonaterAnimInstance->GetAttackIsPlaying())
		return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, true);


	
	Monster->Attack();

	bIsAttacking = true;
	Monster->AttackEnd.AddLambda([this]() -> void { bIsAttacking = false; });



	return EBTNodeResult::InProgress;
}
void UBTTaskMobAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);


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