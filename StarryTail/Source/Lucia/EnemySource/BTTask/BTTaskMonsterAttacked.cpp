// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskMonsterAttacked.h"
#include"../Monster.h"
#include"../MonsterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTaskMonsterAttacked::UBTTaskMonsterAttacked()
{
	NodeName = TEXT("MonsterAttacked");
	bNotifyTick = true;
	WaitTimer = 0.0f;
	
}
EBTNodeResult::Type UBTTaskMonsterAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Monster)
		return EBTNodeResult::Failed;



	//bIsAttacked = true;
	//Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	WaitTime = Monster->GetAttackedTime();

	if (Monster != nullptr) {
		Monster->GetMonsterAnimInstance()->PlayAttackedMontage();
	}

	return EBTNodeResult::InProgress;
}

void UBTTaskMonsterAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	WaitTimer += DeltaSeconds;
	//if (!bIsAttacked)
	//{
	//	OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackedKey, false);
	//	WaitTimer = 0.0f;
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//}
	if (WaitTimer >= WaitTime)
	{
		WaitTimer = 0.0f;

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMonsterAIController::IsAttackedKey, false);			
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
