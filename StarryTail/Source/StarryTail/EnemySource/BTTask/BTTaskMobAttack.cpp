// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMobAttack.h"

#include "../MonsterAIController.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../Ferno/FernoAIController.h"
#include "../Strain/StrainAIController.h"
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



	if (Monster->GetMonsterAtkType() == 2&& OwnerComp.GetBlackboardComponent()->GetValueAsBool(AFernoAIController::IsAfterAttacked)==true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFernoAIController::IsAfterAttacked, false);

		auto ran=FMath::RandRange(1, 100);
		STARRYLOG(Error, TEXT("Attacked Percent : %d"), ran);
		if (ran > Monster->GetAttackPercent())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFernoAIController::IsRunKey, true);

			return EBTNodeResult::Succeeded;
		}
	}
	if (Monster->GetMonsterAtkType() == 2 && OwnerComp.GetBlackboardComponent()->GetValueAsBool(AStrainAIController::IsAfterAttacked) == true)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AStrainAIController::IsAfterAttacked, false);

		auto ran = FMath::RandRange(1, 100);
		STARRYLOG(Error, TEXT("Attacked Percent : %d"), ran);
		if (ran > Monster->GetAttackPercent())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AStrainAIController::IsRunKey, true);

			return EBTNodeResult::Succeeded;
		}
	}

	Monster->GetAIController()->SetAttackCoolKey(true);
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

		if (Monster->GetMonsterAtkType() == 2 && Monster->GetDistanceToPlayer() <= 200.0f)
		{
			
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsRunKey, true);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return;
		}


		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackingKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		Monster->SetIsAttackCool(true);
	}
	
}