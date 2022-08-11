// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskStrainAttacked.h"
#include"../Strain.h"
#include"../StrainAIController.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTaskStrainAttacked::UBTTaskStrainAttacked()
{
	NodeName = TEXT("StrainAttacked");
	bNotifyTick = true;
	WaitTimer = 0.0f;
	
}
EBTNodeResult::Type UBTTaskStrainAttacked::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Strain = Cast<AStrain>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Strain)
		return EBTNodeResult::Failed;



	//bIsAttacked = true;
	//Monster->AttackedEnd.AddLambda([this]() -> void { bIsAttacked = false; });

	WaitTime = Strain->M_Attacked_Time;

	if (Strain != nullptr) {
		Strain->GetStrainAnimInstance()->PlayAttackedMontage();
	}

	STARRYLOG_S(Error);

	return EBTNodeResult::InProgress;
}

void UBTTaskStrainAttacked::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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


		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AStrainAIController::IsAfterAttacked, true);
		WaitTimer = 0.0f;

		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AStrainAIController::IsAttackedKey, false);
		
		
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
