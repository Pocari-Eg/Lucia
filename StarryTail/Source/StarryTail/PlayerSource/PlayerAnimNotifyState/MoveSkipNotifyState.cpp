// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveSkipNotifyState.h"

#include "../IreneCharacter.h"
#include "../PlayerSpirit/IreneSpirit.h"

UMoveSkipNotifyState::UMoveSkipNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UMoveSkipNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);

	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->AddToRoot();
		Irene->IreneAttack->SetCanMoveSkip(true);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneAttack->SetCanMoveSkip(true);
		}
	}
}
void UMoveSkipNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void UMoveSkipNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanMoveSkip(false);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneAttack->SetCanMoveSkip(false);
		}
	}
}

