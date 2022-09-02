﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneUIManager.h"
#include "IreneCharacter.h"
#include "IreneInputInstance.h"
#include "PlayerFSM/IreneFSM.h"

UIreneUIManager::UIreneUIManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_PlayerHud(TEXT("/Game/UI/BluePrint/Player/BP_PlayerHud.BP_PlayerHud_C"));
	if (UI_PlayerHud.Succeeded())
	{
		PlayerHudClass = UI_PlayerHud.Class;
	}
	static ConstructorHelpers::FClassFinder<UPauseWidget>PAUSEWIDGET(TEXT("/Game/UI/BluePrint/Setting/BP_PauseWidget.BP_PauseWidget_C"));
	if (PAUSEWIDGET.Succeeded())
	{
		PauseWidgetClass = PAUSEWIDGET.Class;
	}
	WalkEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_FootStep");
	AttackEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_Attack");
	AttackVoiceEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/Voice/SFX_AttackVoice");
	JumpVoiceEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/Voice/SFX_JumpVoice");
	TakeDamageVoiceEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/Voice/SFX_TakeDamageVoice");
	WaterDodgeEvent= UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_WaterDodge");
	ThunderDodgeEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_ThunderDodge");

	bShowLog = false;
	IsConsecutiveIdle = false;
	CurRecoverWaitTime = 0;
	WalkSoundVolume = 1.0f;
}

void UIreneUIManager::PlayerHudInit()
{
	PlayerHud = CreateWidget<UPlayerHudWidget>(Irene->GetGameInstance(), PlayerHudClass);
	PauseWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseWidgetClass);	
}

void UIreneUIManager::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
	InitMemberVariable();
	PlayerHudInit();

	AttackSound = new SoundManager(AttackEvent, GetWorld());
	WalkSound = new SoundManager(WalkEvent, GetWorld());
	AttackVoiceSound= new SoundManager(AttackVoiceEvent, GetWorld());
	JumpVoiceSound = new SoundManager(JumpVoiceEvent, GetWorld());
	TakeDamageVoiceSound = new SoundManager(TakeDamageVoiceEvent, GetWorld());
	WaterDodgeSound = new SoundManager(WaterDodgeEvent, GetWorld());
	ThunderDodgeSound = new SoundManager(ThunderDodgeEvent, GetWorld());

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
	PauseWidget->AddToViewport();
	

	PlayerHud->AddToViewport();
	PlayerHud->BindCharacter(Irene);
	//사운드 세팅
	WalkSound->SetVolume(WalkSoundVolume);
	WalkSound->SetParameter("Material", 0.0f);

	AttackSound->SetVolume(0.3f);
	AttackSound->SetParameter("Attributes", 2.0f);

	
	AttackVoiceSound->SetVolume(0.3f);
	AttackVoiceSound->SetParameter("Attributes", 2.0f);


	JumpVoiceSound->SetVolume(0.4f);
	TakeDamageVoiceSound->SetVolume(0.4f);
	ThunderDodgeSound->SetVolume(1.0f);

	WaterDodgeSound->SetVolume(1.0f);
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	bIsOnPauseWidget = false;
}

float UIreneUIManager::GetHpRatio()
{
	// 비율변환 0.0 ~ 1.0
	return (Irene->IreneData.CurrentHP < KINDA_SMALL_NUMBER) ? 0.0f : Irene->IreneData.CurrentHP / Irene->IreneData.MaxHP;
}
float UIreneUIManager::GetStaminaRatio()
{
	return (Irene->IreneData.CurrentStamina < KINDA_SMALL_NUMBER) ? 0.0f : Irene->IreneData.CurrentStamina / Irene->IreneData.MaxStamina;
}
void UIreneUIManager::FootStepSound()
{
	WalkSound->SoundPlay3D(Irene->GetActorTransform());
}
void UIreneUIManager::HPRecoveryWaitStart()
{
	if(!Irene->HpRecoveryData.bIsRecovering&& !IsHpFull())
	GetWorld()->GetTimerManager().SetTimer(HpRecoveryWaitTimerHandle, this, &UIreneUIManager::HPRecoveryWaiting, 1.0f, true, 0.0f);
}
void UIreneUIManager::HPRecoveryWaiting()
{
	if (IsConsecutiveIdle == false)
	{
		//STARRYLOG(Warning, TEXT("CurRecoverWaitTime : %d"), CurRecoverWaitTime);
		CurRecoverWaitTime++;
		if (CurRecoverWaitTime >= Irene->HpRecoveryData.Time)HPRecoveringStart();
	}
	else
	{
		//STARRYLOG(Warning, TEXT("CurRecoverWaitTime : %d"), CurRecoverWaitTime);
		CurRecoverWaitTime++;
		if (CurRecoverWaitTime >= Irene->HpRecoveryData.HP_Re_Time)HPRecoveringStart();
	}
}

void UIreneUIManager::HPRecoveryWaitCancel()
{
	CurRecoverWaitTime = 0;
	GetWorld()->GetTimerManager().ClearTimer(HpRecoveryWaitTimerHandle);
	IsConsecutiveIdle = false;
}
void UIreneUIManager::HPRecoveringStart()
{
	Irene->HpRecoveryData.bIsRecovering = true;
	HPRecoveryWaitCancel();
	CurRecoverTime = Irene->HpRecoveryData.Speed;
	RemainingRecovery = Irene->HpRecoveryData.Amount;
	OnHpChanged.Broadcast();
	GetWorld()->GetTimerManager().SetTimer(HpRecoveryTimerHandle, this, &UIreneUIManager::HPRecovering,1.0f , true, 0.0f);
}
void UIreneUIManager::HPRecovering()
{
	if (Irene->HpRecoveryData.bIsRecovering)
	{
		const int CurRecoveryAmount = RemainingRecovery / CurRecoverTime;
		RemainingRecovery -= CurRecoveryAmount;
		if (!IsHpFull())
		{
			Irene->IreneData.CurrentHP += CurRecoveryAmount;
			OnHpChanged.Broadcast();
			if (IsHpFull()) HpRecoveringCancel();
		}
		if (CurRecoverTime > 1)CurRecoverTime--;
		else
		{
			GetWorld()->GetTimerManager().ClearTimer(HpRecoveryTimerHandle);
			RemainingRecovery = 0;
			Irene->HpRecoveryData.bIsRecovering = false;
			IsConsecutiveIdle = true;
			HPRecoveryWaitStart();
			
		}
	}
}
void UIreneUIManager::HpRecoveringCancel()
{
	GetWorld()->GetTimerManager().ClearTimer(HpRecoveryTimerHandle);
	RemainingRecovery = 0;
	Irene->HpRecoveryData.bIsRecovering = false;
	IsConsecutiveIdle = false;
	OnHpChanged.Broadcast();
	if (IsHpFull())Irene->IreneData.CurrentHP = Irene->IreneData.MaxHP;
	else
		HPRecoveryWaitStart();
}
bool UIreneUIManager::IsHpFull()
{
	if (Irene->IreneData.CurrentHP >= Irene->IreneData.MaxHP) return true;
	return false;
}
float UIreneUIManager::GetHpRecoveryRatio()
{
	return ((float)RemainingRecovery < KINDA_SMALL_NUMBER) ? 0.0f : (Irene->IreneData.CurrentHP + (float)RemainingRecovery) / Irene->IreneData.MaxHP;
}

void UIreneUIManager::UpdateFireCool(float CurCool, float MaxCool)
{
	FireCurCoolTime = CurCool;
	FireMaxCoolTime = MaxCool;
}

void UIreneUIManager::UpdateWaterCool(float CurCool, float MaxCool)
{
	WaterCurCoolTime = CurCool;
	WaterMaxCoolTime = MaxCool;
}

void UIreneUIManager::UpdateThunderCool(float CurCool, float MaxCool)
{
	ThunderCurCoolTime = CurCool;
	ThunderMaxCoolTime = MaxCool;
}

float UIreneUIManager::GetFireCoolRatio()
{
	return (FireCurCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (FireCurCoolTime / FireMaxCoolTime);
}

float UIreneUIManager::GetWaterCoolRatio()
{
	return (WaterCurCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (WaterCurCoolTime / WaterMaxCoolTime);
}

float UIreneUIManager::GetThunderCoolRatio()
{
	return (ThunderCurCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (ThunderCurCoolTime / ThunderMaxCoolTime);
}

float UIreneUIManager::GetFireSkillCoolRatio()
{
	return (FireSkillCurCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (FireSkillCurCoolTime / FireSkillMaxCoolTime);
}

float UIreneUIManager::GetWaterSkillCoolRatio()
{
	return (WaterSkillCurCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (WaterSkillCurCoolTime / WaterSkillMaxCoolTime);
}

float UIreneUIManager::GetThunderSkillCoolRatio()
{
	return (ThunderSkillCurCoolTime < KINDA_SMALL_NUMBER) ? 0.0f : (ThunderSkillCurCoolTime / ThunderSkillMaxCoolTime);
}

int UIreneUIManager::GetSkillCount()
{
	return Irene->IreneInput->GetThunderSkillCount();
}

void UIreneUIManager::SetSkillCount(int Value)
{
	Irene->IreneInput->SetThunderSkillCount(Value);
}

void UIreneUIManager::PlayHUDAnimation()
{
	PlayerHud->PlayHUDAnimation();
}

void UIreneUIManager::UpdateWaterSkillCool(float CurCool, float MaxCool)
{
	WaterSkillCurCoolTime = CurCool;
	WaterSkillMaxCoolTime = MaxCool;
}

void UIreneUIManager::UpdateThunderSkillCool(float CurCool, float MaxCool)
{
	ThunderSkillCurCoolTime = CurCool;
	ThunderSkillMaxCoolTime = MaxCool;
}

void UIreneUIManager::UpdateFireSkillCool(float CurCool, float MaxCool)
{

	FireSkillCurCoolTime = CurCool;
	FireSkillMaxCoolTime = MaxCool;
}

void UIreneUIManager::SetDialogState(const bool State)
{
	Irene->IreneInput->SetDialogState(State);
}

void UIreneUIManager::HpFullRecovery()
{
	Irene->IreneData.CurrentHP = Irene->IreneData.MaxHP;
	HpRecoveringCancel();
}



void UIreneUIManager::PauseWidgetOn()
{
	bIsOnPauseWidget = true;
	PlayerHud->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->WidgetOn();
}

void UIreneUIManager::PauseWidgetOff()
{
	if (PauseWidget->WidgetOff()) {
		bIsOnPauseWidget = false;

		PlayerHud->SetVisibility(ESlateVisibility::Visible);
	}
}

bool UIreneUIManager::GetIsPauseOnScreen()
{
	return bIsOnPauseWidget;
}

