// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScChange.h"
#include "../Scientia.h"
#include "../ScAIController.h"

UBTTaskScChange::UBTTaskScChange()
{
	NodeName = TEXT("Change");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskScChange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	Scientia->Change();

	Scientia->SetState(TEXT("Change"));

	bIsChange = true;

	Scientia->ChangeEnd.AddLambda([this]() -> void
		{
			bIsChange = false;
		});

	return EBTNodeResult::InProgress;
}
void UBTTaskScChange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsChange)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsChangeKey, false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
