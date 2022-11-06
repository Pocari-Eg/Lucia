// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskWalkR.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../STGameInstance.h"
UBTTaskWalkR::UBTTaskWalkR()
{
	NodeName = TEXT("Battle_Walk_R");
	bNotifyTick = true;

	
	WalkTimer = 0.0f;
}

EBTNodeResult::Type UBTTaskWalkR::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bouldelith)
		return EBTNodeResult::Failed;

	Bouldelith->GetBouldelithAnimInstance()->PlayRightBattleWalkMontage();


	WalkTime = FMath::FRandRange(Bouldelith->GetMinSupportWalkTime(), Bouldelith->GetMaxSupportWalkTime());

	return EBTNodeResult::InProgress;
}

void UBTTaskWalkR::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	//È¸Àü
	Monster->RotationPlayer(DeltaSeconds);
	WalkTimer += DeltaSeconds;
	if (WalkTimer >= WalkTime)
	{
		WalkTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	}


