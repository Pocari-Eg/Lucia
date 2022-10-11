// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillSkipNotifyState.h"
#include "../PlayerSpirit/IreneSpirit.h"
#include "../IreneCharacter.h"

USkillSkipNotifyState::USkillSkipNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void USkillSkipNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);
	
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanSkillSkip(true);
		Irene->AddToRoot();
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneAttack->SetCanSkillSkip(true);
		}
	}
}
void USkillSkipNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void USkillSkipNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanSkillSkip(false);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneAttack->SetCanSkillSkip(true);
		}
	}
}

