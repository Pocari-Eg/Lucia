// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSkipNotifyState.h"

#include "../IreneCharacter.h"

USkillSkipNotifyState::USkillSkipNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void USkillSkipNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);

	Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		//Irene->IreneAttack->SetCanSkillSkip(true);
	}
}
void USkillSkipNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void USkillSkipNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	if(Irene != nullptr)
	{
		//Irene->IreneAttack->SetCanSkillSkip(false);
	}
}

