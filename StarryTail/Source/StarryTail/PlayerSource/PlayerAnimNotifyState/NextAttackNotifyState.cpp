// Fill out your copyright notice in the Description page of Project Settings.


#include "NextAttackNotifyState.h"

#include "../IreneCharacter.h"
#include "../PlayerInstance/IreneAnimInstance.h"
#include "../PlayerInstance/IreneInputInstance.h"
#include "../PlayerSpirit/IreneSpirit.h"
#include "../PlayerSpirit/IreneSpiritAnimInstance.h"
#include "../PlayerFSM/IreneFSM.h"

UNextAttackNotifyState::UNextAttackNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UNextAttackNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->AddToRoot();
		Irene->IreneData.CanNextCombo = true;
		Irene->IreneInput->SetNextAttack(true);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneData.CanNextCombo = true;
			Spirit->Irene->IreneInput->SetNextAttack(true);
		}
	}
}
void UNextAttackNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
}
void UNextAttackNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	const auto Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneData.CanNextCombo = false;
		if (Irene->IreneData.IsComboInputOn)
		{
			Irene->IreneAttack->AttackStartComboState();
			Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
		}
		Irene->IreneInput->SetNextAttack(false);
	}
	else
	{
		const auto Spirit = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneSpirit>();
		if(Spirit != nullptr)
		{
			Spirit->Irene->IreneData.CanNextCombo = false;
			if (Spirit->Irene->IreneData.IsComboInputOn)
			{
				Spirit->Irene->IreneAttack->AttackStartComboState();
				if(Spirit->Irene->IreneSpirit != nullptr)
				{
					if(Spirit->Irene->IreneState->GetStateToString().Compare(FString("Spirit_Skill_3")) != 0)
					{
						Spirit->Irene->IreneSpirit->IreneSpiritAnim->JumpToAttackMontageSection(Spirit->Irene->IreneData.CurrentCombo);
						Spirit->Irene->IreneAttack->SetSkillState();
					}
				}
			}
			Spirit->Irene->IreneInput->SetNextAttack(false);
		}
	}
}
