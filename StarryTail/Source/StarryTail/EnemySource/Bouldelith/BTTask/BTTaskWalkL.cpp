// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskWalkL.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../STGameInstance.h"
UBTTaskWalkL::UBTTaskWalkL()
{
	NodeName = TEXT("Battle_Walk_L");
	bNotifyTick = true;

	 WalkTimer=0.0f;
}

EBTNodeResult::Type UBTTaskWalkL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bouldelith)
		return EBTNodeResult::Failed;

	Bouldelith->GetBouldelithAnimInstance()->PlayLeftBattleWalkMontage();

	WalkTime = FMath::FRandRange(Bouldelith->GetMinSupportWalkTime(), Bouldelith->GetMaxSupportWalkTime());
	return EBTNodeResult::InProgress;
}

void UBTTaskWalkL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());

	////È¸Àü
	Monster->RotationPlayer(DeltaSeconds);
	WalkTimer += DeltaSeconds;
	if (WalkTimer >= WalkTime)
	{
		WalkTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}


