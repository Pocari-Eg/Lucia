// Fill out your copyright notice in the Description page of Project Settings.


#include "IreneUIManager.h"
#include "IreneCharacter.h"

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