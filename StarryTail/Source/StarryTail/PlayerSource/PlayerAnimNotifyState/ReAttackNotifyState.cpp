// Fill out your copyright notice in the Description page of Project Settings.


#include "ReAttackNotifyState.h"

#include "../IreneCharacter.h"
#include "StarryTail/PlayerSource/PlayerInstance/IreneInputInstance.h"

UReAttackNotifyState::UReAttackNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UReAttackNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);

	Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneInput->SetReAttack(true);
	}
}
void UReAttackNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void UReAttackNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);

	if(Irene != nullptr)
	{
		Irene->IreneInput->SetReAttack(false);
	}
}