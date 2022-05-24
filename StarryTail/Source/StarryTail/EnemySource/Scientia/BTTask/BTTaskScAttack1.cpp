// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScAttack1.h"
#include "../Scientia.h"
#include "../ScAIController.h"

UBTTaskScAttack1::UBTTaskScAttack1()
{
	NodeName = TEXT("Attack1");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskScAttack1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	Scientia->Attack1();

	Scientia->SetState(TEXT("Attack1"));

	bIsAttacking = true;

	WaitTime = 1.4f;
	WaitTimer = 0.0f;

	Scientia->Attack1End.AddLambda([this]() -> void { bIsAttacking = false; });

	return EBTNodeResult::InProgress;
}
void UBTTaskScAttack1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	if (Scientia->GetFeatherCount() > 0)
	{
		WaitTimer += DeltaSeconds;

		if (WaitTimer >= WaitTime)
		{
			Scientia->Attack1();
			WaitTimer = 0.0f;
		}
		if (!bIsAttacking)
		{
			Scientia->ResetFeatherCount();

			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttackingKey, false);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsAttack1Key, false);
			if (Scientia->GetHpPercent() < 40)
				return; // Drop
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}
}
