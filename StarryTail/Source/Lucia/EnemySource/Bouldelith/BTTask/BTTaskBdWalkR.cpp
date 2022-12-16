// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdWalkR.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../STGameInstance.h"
UBTTaskBdWalkR::UBTTaskBdWalkR()
{
	NodeName = TEXT("Battle_Walk_R");
	bNotifyTick = true;

	
	WalkTimer = 0.0f;
}

EBTNodeResult::Type UBTTaskBdWalkR::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bouldelith = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bouldelith)
		return EBTNodeResult::Failed;


	Bouldelith->InitWalkSpeed();
	Bouldelith->GetBouldelithAnimInstance()->PlayRightBattleWalkMontage();


	WalkTime = FMath::FRandRange(Bouldelith->GetMinSupportWalkTime(), Bouldelith->GetMaxSupportWalkTime());

	return EBTNodeResult::InProgress;
}

void UBTTaskBdWalkR::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABouldelith>(OwnerComp.GetAIOwner()->GetPawn());
	FVector Forward = Monster->GetActorForwardVector();
	Forward.Normalize();
	FVector RightDirection = Forward.RotateAngleAxis(90.0f, FVector::UpVector);
	Monster->SetActorLocation(Monster->GetActorLocation() + (RightDirection * Monster->GetMoveSpeed() * DeltaSeconds));
	//È¸Àü
	Monster->RotationPlayer(DeltaSeconds);
	WalkTimer += DeltaSeconds;
	if (WalkTimer >= WalkTime)
	{
		WalkTimer = 0.0f;
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	}


