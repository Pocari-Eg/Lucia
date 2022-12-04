// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpAttackNotifyState.h"

#include "../IreneCharacter.h"
#include "../PlayerInstance/IreneInputInstance.h"
#include "../PlayerSpirit/IreneSpirit.h"

UJumpAttackNotifyState::UJumpAttackNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UJumpAttackNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);

	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneInput->SetJumpAttack(true);
	}
}
void UJumpAttackNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void UJumpAttackNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);

	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneInput->SetJumpAttack(false);
	}
}