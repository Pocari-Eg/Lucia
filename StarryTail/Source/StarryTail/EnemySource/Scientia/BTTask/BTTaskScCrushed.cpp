// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskScCrushed.h"
#include "../Scientia.h"
#include "../ScAIController.h"

UBTTaskScCrushed::UBTTaskScCrushed()
{
	NodeName = TEXT("Crushed");
	bNotifyTick = true;
}
EBTNodeResult::Type UBTTaskScCrushed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

	Scientia->Crushed();

	bIsCrushed = true;

	Scientia->CrushedEnd.AddLambda([this]() -> void {
		bIsCrushed = false;
		});
	
	return EBTNodeResult::InProgress;
}
void UBTTaskScCrushed::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!bIsCrushed)
	{
		auto Scientia = Cast<AScientia>(OwnerComp.GetAIOwner()->GetPawn());

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsCrushedKey, false);
		
		if (Scientia->GetBarrierCount() == 2)
		{
			// 살짝 금 간 텍스쳐
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsChangeKey, true);
		}
		else if (Scientia->GetBarrierCount() == 1)
		{
			// 많이 금 간 텍스쳐
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(AScAIController::IsChangeKey, true);
		}
		else if (Scientia->GetBarrierCount() == 0)
		{
			//완전히 금 간 텍스쳐
			Scientia->SetAttribute(EAttributeKeyword::e_None);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}