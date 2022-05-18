// Fill out your copyright notice in the Description page of Project Settings.


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
	static ConstructorHelpers::FClassFinder<UPauseWidget>PAUSEWIDGET(TEXT("/Game/UI/BluePrint/BP_PauseWidget.BP_PauseWidget_C"));
	if (PAUSEWIDGET.Succeeded())
	{
		PauseWidgetClass = PAUSEWIDGET.Class;
	}
	WalkEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_FootStep");
	AttackEvent = UFMODBlueprintStatics::FindEventByName("event:/StarryTail/Irene/SFX_Attack");

	bShowLog = false;
	IsConsecutiveIdle = false;
	CurRecoverWaitTime = 0;
	WalkSoundVolume = 0.7f;
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
	PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerHud->AddToViewport();
	PlayerHud->BindCharacter(Irene);
	//사운드 세팅
	WalkSound->SetVolume(WalkSoundVolume);
	AttackSound->SetParameter("Material", 0.0f);

	AttackSound->SetVolume(0.3f);
	AttackSound->SetParameter("Attributes", 1.0f);
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

void UIreneUIManager::PauseWidgetOn()
{
	GetWorld()->GetFirstPlayerController()->bShowMouseCursor;
	PlayerHud->SetVisibility(ESlateVisibility::Hidden);
	PauseWidget->WidgetOn();
}
