// Fill out your copyright notice in the Description page of Project Settings.


#include "NextAttackNotifyState.h"

#include "../IreneCharacter.h"
#include "../PlayerInstance/IreneAnimInstance.h"
#include "../PlayerInstance/IreneInputInstance.h"

UNextAttackNotifyState::UNextAttackNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UNextAttackNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);
	Irene = BranchingPointPayload.SkelMeshComponent->GetOwner<AIreneCharacter>();
	if(Irene != nullptr)
	{
		Irene->IreneData.CanNextCombo = true;
	}
}
void UNextAttackNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(BranchingPointPayload, FrameDeltaTime);
}
void UNextAttackNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	STARRYLOG_S(Warning);
	if(Irene != nullptr)
	{
		Irene->IreneData.CanNextCombo = false;
		if (Irene->IreneData.IsComboInputOn)
		{
			Irene->IreneAttack->AttackStartComboState();
			Irene->IreneAnim->JumpToAttackMontageSection(Irene->IreneData.CurrentCombo);
		}
		Irene->IreneInput->SetReAttack(true);
	}
}
