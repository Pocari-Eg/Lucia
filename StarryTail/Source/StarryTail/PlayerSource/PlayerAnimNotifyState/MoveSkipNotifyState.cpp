// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSkipNotifyState.h"

#include "../IreneCharacter.h"

UMoveSkipNotifyState::UMoveSkipNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UMoveSkipNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);

	Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanMoveSkip(true);
	}
}
void UMoveSkipNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void UMoveSkipNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanMoveSkip(false);
	}
}

