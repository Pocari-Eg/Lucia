// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillToAttackNotifyState.h"

#include "../PlayerSpirit/IreneSpirit.h"
#include "../IreneCharacter.h"

USkillToAttackNotifyState::USkillToAttackNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void USkillToAttackNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);
	
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanSkillToAttack(true);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneAttack->SetCanSkillToAttack(true);
		}
	}
}
void USkillToAttackNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
	
}
void USkillToAttackNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneAttack->SetCanSkillToAttack(false);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneAttack->SetCanSkillToAttack(true);
		}
	}
}