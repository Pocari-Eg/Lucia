// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBfWalkL.h"
#include "../Bellyfish.h"
#include "../BellyfishAIController.h"
#include "../../../STGameInstance.h"
UBTTaskBfWalkL::UBTTaskBfWalkL()
{
	NodeName = TEXT("Battle_Walk_L");
	bNotifyTick = true;

	 WalkTimer=0.0f;
}

EBTNodeResult::Type UBTTaskBfWalkL::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto Bellyfish = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == Bellyfish)
		return EBTNodeResult::Failed;

	Bellyfish->PlayWalkAnim();

	WalkTime = FMath::FRandRange(Bellyfish->GetMinSupportWalkTime(), Bellyfish->GetMaxSupportWalkTime());
	return EBTNodeResult::InProgress;
}

void UBTTaskBfWalkL::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto Monster = Cast<ABellyfish>(OwnerComp.GetAIOwner()->GetPawn());


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


