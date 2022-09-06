// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBellyfishAttacked.h"
#include"../Bellyfish.h"
#include"../BellyfishAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTaskBellyfishAttacked::UBTTaskBellyfishAttacked()
{
	NodeName = TEXT("BellyfishAttacked");
	bNotifyTick = true;
	WaitTimer = 0.0f;
	
}
EBTNodeResult::Type UBTTaskBellyfishAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bellyfish)
		return EBTNodeResult::Failed;



	//bIsAttacked = true;
	//Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	WaitTime = Bellyfish->GetAttackedTime();

	if (Bellyfish != nullptr) {
		Bellyfish->GetBellyfishAnimInstance()->PlayAttackedMontage();
	}

	STARRYLOG_S(Error);

	return EBTNodeResult::InProgress;
}

void UBTTaskBellyfishAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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


		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAfterAttacked, true);
		WaitTimer = 0.0f;

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABellyfishAIController::IsAttackedKey, false);
		
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
