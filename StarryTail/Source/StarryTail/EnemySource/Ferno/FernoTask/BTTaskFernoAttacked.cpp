// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskFernoAttacked.h"
#include"../Ferno.h"
#include"../FernoAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTaskFernoAttacked::UBTTaskFernoAttacked()
{
	NodeName = TEXT("FernoAttacked");
	bNotifyTick = true;
	WaitTimer = 0.0f;
	WaitTime = 0.5;
}
EBTNodeResult::Type UBTTaskFernoAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Ferno = Cast<AFerno>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Ferno)
		return EBTNodeResult::Failed;



	//bIsAttacked = true;
	//Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	if (Ferno != nullptr) {
		Ferno->GetFernoAnimInstance()->PlayAttackedMontage();
	}

	STARRYLOG_S(Error);

	return EBTNodeResult::InProgress;
}

void UBTTaskFernoAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AFernoAIController::IsAttackedKey, false);
		WaitTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
