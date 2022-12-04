// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBfWalkR.h"
#include "../Bellyfish.h"
#include "../BellyfishAIController.h"
#include "../../../STGameInstance.h"
UBTTaskBfWalkR::UBTTaskBfWalkR()
{
	NodeName = TEXT("Battle_Walk_R");
	bNotifyTick = true;

	
	WalkTimer = 0.0f;
}

EBTNodeResult::Type UBTTaskBfWalkR::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bellyfish)
		return EBTNodeResult::Failed;


	Bellyfish->PlayWalkAnim();


	WalkTime = FMath::FRandRange(Bellyfish->GetMinSupportWalkTime(), Bellyfish->GetMaxSupportWalkTime());

	return EBTNodeResult::InProgress;
}

void UBTTaskBfWalkR::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
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


