﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneUIManager.h"
#include "IreneCharacter.h"
#include "IreneFSM.h"

UIreneUIManager::UIreneUIManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_PlayerHud(TEXT("/Game/UI/BluePrint/BP_PlayerHud.BP_PlayerHud_C"));
	if (UI_PlayerHud.Succeeded())
	{
		PlayerHudClass = UI_PlayerHud.Class;
	}

	WalkEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_FootStep");
	AttackEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_Attack");

	bShowLog = false;
	CurRecoverWaitTime = 0;
}

void UIreneUIManager::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
}
void UIreneUIManager::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
void UIreneUIManager::InitMemberVariable()
{
	
}
void UIreneUIManager::Begin()
{
	PlayerHud = CreateWidget<UPlayerHudWidget>(Irene->GetGameInstance(), PlayerHudClass);
	PlayerHud->AddToViewport();
	PlayerHud->BindCharacter(Irene);
	PlayerHud->FireAttributesOn();
	//사운드 세팅
	AttackSound = new SoundManager(AttackEvent, GetWorld());
	AttackSound->SetVolume(0.3f);
	AttackSound->SetParameter("Attributes", 0.0f);
	WalkSound = new SoundManager(WalkEvent, GetWorld());
	WalkSound->SetVolume(WalkSoundVolume);
	AttackSound->SetParameter("Material", 0.0f);
}

float UIreneUIManager::GetHpRatio()
{
	// 비율변환 0.0 ~ 1.0
	return (Irene->IreneData.CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : Irene->IreneData.CurrentHP / Irene->IreneData.MaxHP;
}
float UIreneUIManager::GetMpRatio()
{
	return (Irene->IreneData.CurrentMP < KINDA_SMALL_NUMBER) ? 0.0f : Irene->IreneData.CurrentMP / Irene->IreneData.MaxMP;
}
void UIreneUIManager::FootStepSound()
{
	WalkSound->SoundPlay3D(Irene->GetActorTransform());
}
void UIreneUIManager::HPRecoveryWaitStart()
{
	if(!Irene->HpRecoveryData.bIsRecovering&& !IsHpFull())
	GetWorld()->GetTimerManager().SetTimer(HpRecorveryWaitTimerHandle, this, &UIreneUIManager::HPRecoveryWaiting, 1.0f, true, 0.0f);
}
void UIreneUIManager::HPRecoveryWaiting()
{
    if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) != 0)	HPRecoveryWaitCancel();
	else {
		STARRYLOG(Warning, TEXT("CurRecoverWaitTime : %d"), CurRecoverWaitTime);
		CurRecoverWaitTime++;
		if (CurRecoverWaitTime >= Irene->HpRecoveryData.Time)HPRecoveringStart();
	}
}
void UIreneUIManager::HPRecoveryWaitCancel()
{
	CurRecoverWaitTime = 0;
	GetWorld()->GetTimerManager().ClearTimer(HpRecorveryWaitTimerHandle);
}
void UIreneUIManager::HPRecoveringStart()
{
	Irene->HpRecoveryData.bIsRecovering = true;
	HPRecoveryWaitCancel();
	CurRecoverTime = Irene->HpRecoveryData.Speed;
	RemainingRecovry = Irene->HpRecoveryData.Amount;
	OnHpChanged.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(HpRecorveryTimerHandle, this, &UIreneUIManager::HPRecovering,1.0f , true, 0.0f);
}
void UIreneUIManager::HPRecovering()
{
	if (Irene->IreneState->GetStateToString().Compare(FString("Idle")) != 0)
	{
		HpRecoveringCancel();
	}

	if (Irene->HpRecoveryData.bIsRecovering) {
		int CurRecoveryAmount = RemainingRecovry / CurRecoverTime;
		RemainingRecovry -= CurRecoveryAmount;
		if (!IsHpFull())
		{
			Irene->IreneData.CurrentHP += CurRecoveryAmount;
			OnHpChanged.Broadcast();
			if (IsHpFull()) HpRecoveringCancel();
		}
		if (CurRecoverTime > 1)CurRecoverTime--;
		else HpRecoveringCancel();
	}
}
void UIreneUIManager::HpRecoveringCancel()
{
	GetWorld()->GetTimerManager().ClearTimer(HpRecorveryTimerHandle);
	RemainingRecovry = 0;
	Irene->HpRecoveryData.bIsRecovering = false;
	OnHpChanged.Broadcast();
	if (IsHpFull())Irene->IreneData.CurrentHP = Irene->IreneData.MaxHP;
	else {
		HPRecoveryWaitStart();
	}
}
bool UIreneUIManager::IsHpFull()
{
	if (Irene->IreneData.CurrentHP >= Irene->IreneData.MaxHP)	return true;
	else {
		return false;
	}
}
float UIreneUIManager::GetHpRecoveryRatio()
{
	return ((float)RemainingRecovry < KINDA_SMALL_NUMBER) ? 0.0f : (Irene->IreneData.CurrentHP + (float)RemainingRecovry) / Irene->IreneData.MaxHP;
}