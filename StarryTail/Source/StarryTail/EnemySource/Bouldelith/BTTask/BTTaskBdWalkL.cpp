// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdWalkL.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../STGameInstance.h"
UBTTaskBdWalkL::UBTTaskBdWalkL()
{
	NodeName = TEXT("Battle_Walk_L");
	bNotifyTick = true;

	 WalkTimer=0.0f;
}

EBTNodeResult::Type UBTTaskBdWalkL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bouldelith)
		return EBTNodeResult::Failed;

	Bouldelith->InitWalkSpeed();
	Bouldelith->GetBouldelithAnimInstance()->PlayLeftBattleWalkMontage();

	WalkTime = FMath::FRandRange(Bouldelith->GetMinSupportWalkTime(), Bouldelith->GetMaxSupportWalkTime());
	return EBTNodeResult::InProgress;
}

void UBTTaskBdWalkL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());


	FVector Forward = Monster->GetActorForwardVector();
	Forward.Normalize();
	FVector LeftDirection = Forward.RotateAngleAxis(-90.0f, FVector::UpVector);
	Monster->SetActorLocation(Monster->GetActorLocation() + (LeftDirection * Monster->GetMoveSpeed() * DeltaSeconds));

	////È¸Àü
	Monster->RotationPlayer(DeltaSeconds);
	WalkTimer += DeltaSeconds;
	if (WalkTimer >= WalkTime)
	{
		WalkTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}


