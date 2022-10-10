// Fill out your copyright notice in the Description page of Project Settings.

#include "IreneFSM.h"
#include "../IreneCharacter.h"
#include "../PlayerInstance/IreneInputInstance.h"
#include "../PlayerInstance/IreneUIManager.h"
#include "../PlayerInstance/IreneAnimInstance.h"
#include "../PlayerInstance/IreneAttackInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "../PlayerSpirit/IreneSpirit.h"
#include "../PlayerSpirit/IreneSpiritAnimInstance.h"

#pragma region IreneFSM
void UIreneFSM::Update(const float Value)
{
	this->PlayTime += Value;
	StateValue->Execute(this);
}
void UIreneFSM::ChangeState(IState* NewState)
{
	StateValue->Exit(this);
	StateValue = NewState;
	StateValue->Enter(this);
}
void UIreneFSM::ThrowState(IState* NewState)
{
	NewState->Enter(this);
	NewState->Exit(this);
}
void UIreneFSM::Init(AIreneCharacter* Value)
{
	SetIreneCharacter(Value);
}
void UIreneFSM::SetIreneCharacter(AIreneCharacter* Value)
{
	Irene = Value;
}
FString UIreneFSM::GetStateToString() const
{
	switch (StateEnumValue)
	{
	case EStateEnum::Idle: return FString("Idle");
	case EStateEnum::BattleIdle: return FString("BattleIdle");
	case EStateEnum::Run_Loop: return FString("Run_Loop");
	case EStateEnum::Run_End: return FString("Run_End");
	case EStateEnum::Sprint_Loop: return FString("Sprint_Loop");
	case EStateEnum::Sprint_End: return FString("Sprint_End");
	case EStateEnum::Dodge_Start: return FString("Dodge_Start");
	case EStateEnum::Dodge_End: return FString("Dodge_End");
	case EStateEnum::Jump_Start: return FString("Jump_Start");
	case EStateEnum::Jump_Loop: return FString("Jump_Loop");
	case EStateEnum::Jump_End: return FString("Jump_End");
	case EStateEnum::B_Attack_1: return FString("B_Attack_1");
	case EStateEnum::B_Attack_2: return FString("B_Attack_2");
	case EStateEnum::B_Attack_3: return FString("B_Attack_3");
	case EStateEnum::Sword_Skill_1: return FString("Sword_Skill_1");
	case EStateEnum::Sword_Skill_2: return FString("Sword_Skill_2");
	case EStateEnum::Spirit_Skill_1: return FString("Spirit_Skill_1");
	case EStateEnum::Spirit_Skill_2: return FString("Spirit_Skill_2");
	case EStateEnum::Spirit_Skill_3: return FString("Spirit_Skill_3");
	case EStateEnum::Form_Change: return FString("Form_Change");
	case EStateEnum::Hit_1: return FString("Hit_1");
	case EStateEnum::Hit_2: return FString("Hit_2");
	case EStateEnum::KnockBack: return FString("KnockBack");
	case EStateEnum::Death: return FString("Death");
	default: return FString("Error StateEnumToString");
	}
}
#pragma endregion IreneFSM

#pragma region IdleState
#pragma region UIdleState
UIdleState* UIdleState::GetInstance()
{
	static UIdleState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UIdleState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UIdleState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Idle);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	// Irene이 없으면 UI메니저 확인 안함
	if (CurState->Irene && CurState->Irene->IreneUIManager)
		CurState->Irene->IreneUIManager->HPRecoveryWaitStart();
	if (CurState->Irene != nullptr)
	{
		if (CurState->Irene->Weapon->IsVisible())
		{
			CurState->Irene->Weapon->SetVisibility(false);
			CurState->Irene->WeaponVisible(false);
		}
	}
}

void UIdleState::Execute(IBaseGameEntity* CurState)
{

}

void UIdleState::Exit(IBaseGameEntity* CurState)
{
	if (CurState->Irene->HpRecoveryData.bIsRecovering == true)CurState->Irene->IreneUIManager->HpRecoveringCancel();
	else CurState->Irene->IreneUIManager->HPRecoveryWaitCancel();
	CurState->bIsEnd = true;
}
#pragma endregion IdleState
#pragma region UBattleIdleState
UBattleIdleState* UBattleIdleState::GetInstance()
{
	static UBattleIdleState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UBattleIdleState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UBattleIdleState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::BattleIdle);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UBattleIdleState::Execute(IBaseGameEntity* CurState)
{
	if (CurState->PlayTime >= 10.0f)
	{
		CurState->Irene->Weapon->SetVisibility(false);
		CurState->Irene->WeaponVisible(false);
		CurState->Irene->ChangeStateAndLog(UIdleState::GetInstance());
	}
}

void UBattleIdleState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion UBattleIdleState
#pragma endregion IdleState

#pragma region RunState
#pragma region URunLoopState
URunLoopState* URunLoopState::GetInstance()
{
	static URunLoopState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<URunLoopState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void URunLoopState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Run_Loop);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	if(CurState->Irene->bIsSpiritStance)
	{
		CurState->Irene->ChangeStateAndLog(USprintLoopState::GetInstance());
		return;
	}	
	CurState->Irene->GetCharacterMovement()->MaxWalkSpeed = CurState->Irene->IreneData.RunMaxSpeed * CurState->Irene->IreneData.WaterDeBuffSpeed;
	if (CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->Weapon->SetVisibility(false);
		CurState->Irene->WeaponVisible(false);
	}
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.IsComboInputOn = false;
	CurState->Irene->IreneData.CurrentCombo = 0;
	//CurState->Irene->SetCameraLagTime(0);
}

void URunLoopState::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveForward();
	CurState->Irene->IreneInput->MoveRight();

	const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
	if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
	{
		// if (Irene->IreneState->GetStateToString().Compare(FString("Sprint")) == 0)
		// {
		// 	Irene->IreneAnim->SetSprintStopAnim(true);
		// 	FTimerHandle TimerHandle;
		// 	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		// 		{
		// 			Irene->IreneAnim->SetSprintStopAnim(false);
		// 		}, 0.3f, false);
		// }
		//CurState->Irene->ChangeStateAndLog(URunEndState::GetInstance());
		CurState->ThrowState(URunEndState::GetInstance());
		CurState->Irene->ActionEndChangeMoveState();
	}
	if(CurState->Irene->CameraLagCurve.Num()>0)
	{
		if (MoveKey[0] != 0)
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[0]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 12;
		}
		if (MoveKey[2] != 0)
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[3]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 12;
		}
		if (MoveKey[1] != 0 || MoveKey[3] != 0)
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[1]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 14;
		}
		if ((MoveKey[0] != 0 && MoveKey[1] != 0) || (MoveKey[0] != 0 && MoveKey[3] != 0) ||
			(MoveKey[2] != 0 && MoveKey[1] != 0) || (MoveKey[2] != 0 && MoveKey[3] != 0))
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[2]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 12;
		}
	}

	//대각선이 아니면
	if (!((MoveKey[0] != 0 && (MoveKey[1] != 0 || MoveKey[3] != 0)) || (MoveKey[2] != 0 && (MoveKey[1] != 0 || MoveKey[3] != 0))))
	{
		if (MoveKey[0] != 0 && MoveKey[2] != 0)
		{
			CurState->ThrowState(URunEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(UIdleState::GetInstance());
		}
		if (MoveKey[1] != 0 && MoveKey[3] != 0)
		{
			CurState->ThrowState(URunEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(UIdleState::GetInstance());
		}
	}
}

void URunLoopState::Exit(IBaseGameEntity* CurState)
{
	CurState->ThrowState(URunEndState::GetInstance());
	CurState->bIsEnd = true;
}
#pragma endregion URunLoopState
#pragma region URunEndState
URunEndState* URunEndState::GetInstance()
{
	static URunEndState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<URunEndState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void URunEndState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Run_End);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void URunEndState::Execute(IBaseGameEntity* CurState)
{
	//CurState->Irene->ActionEndChangeMoveState();
}

void URunEndState::Exit(IBaseGameEntity* CurState)
{
	//CurState->Irene->SetCameraLagTime(0);
	//CurState->Irene->SetLastLagTime(CurState->Irene->SpringArmComp->CameraLagSpeed);
	if(CurState->Irene->CameraLagCurve.Num()>0)
	{
		CurState->Irene->SpringArmComp->CameraLagSpeed = 10;
		CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[9]);
	}
	CurState->bIsEnd = true;
}
#pragma endregion URunEndState
#pragma endregion RunState

#pragma region SprintState
#pragma region USprintLoopState
USprintLoopState* USprintLoopState::GetInstance()
{
	static USprintLoopState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USprintLoopState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USprintLoopState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Sprint_Loop);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurState->Irene->GetCharacterMovement()->MaxWalkSpeed = CurState->Irene->IreneData.SprintMaxSpeed * CurState->Irene->IreneData.WaterDeBuffSpeed;
	CurState->Irene->IreneAnim->SetSprintStateAnim(true);
	ChangeMoveKey = CurState->Irene->IreneInput->MoveKey;
	//CurState->Irene->SetCameraLagTime(0);
	if (CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->Weapon->SetVisibility(false);
		CurState->Irene->WeaponVisible(false);
	}
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.IsComboInputOn = false;
	CurState->Irene->IreneData.CurrentCombo = 0;
	CurState->Irene->IreneAnim->SetSprintPlayRate(1.0f);

	if(CurState->Irene->bIsSpiritStance)
	{
		CurState->Irene->GetCharacterMovement()->MaxWalkSpeed = CurState->Irene->IreneData.SprintMaxSpeed * CurState->Irene->IreneData.WaterDeBuffSpeed * 1.5f;
		CurState->Irene->IreneAnim->SetSprintPlayRate(1.5f);
	}
}

void USprintLoopState::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveForward();
	CurState->Irene->IreneInput->MoveRight();
	const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
	if (MoveKey[0] == 0 && MoveKey[1] == 0 && MoveKey[2] == 0 && MoveKey[3] == 0)
	{
		// if (Irene->IreneState->GetStateToString().Compare(FString("Sprint")) == 0)
		// {
		// 	Irene->IreneAnim->SetSprintStopAnim(true);
		// 	FTimerHandle TimerHandle;
		// 	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
		// 		{
		// 			Irene->IreneAnim->SetSprintStopAnim(false);
		// 		}, 0.3f, false);
		// }
		CurState->ThrowState(USprintEndState::GetInstance());
		CurState->Irene->ActionEndChangeMoveState();
	}
	if(CurState->Irene->CameraLagCurve.Num()>0)
	{
		if (MoveKey[0] != 0)
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[4]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 10;
		}
		if (MoveKey[2] != 0)
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[7]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 10;
		}
		if (MoveKey[1] != 0 || MoveKey[3] != 0)
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[5]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 12;
		}
		if ((MoveKey[0] != 0 && MoveKey[1] != 0) || (MoveKey[0] != 0 && MoveKey[3] != 0) ||
			(MoveKey[2] != 0 && MoveKey[1] != 0) || (MoveKey[2] != 0 && MoveKey[3] != 0))
		{
			CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[6]);
			CurState->Irene->SpringArmComp->CameraLagSpeed = 10;
		}
	}
	// w,a,s,d -> 0,1,2,3
	//대각선이면
	if ((ChangeMoveKey[0] != 0 && (ChangeMoveKey[1] != 0 || ChangeMoveKey[3] != 0)) || (ChangeMoveKey[2] != 0 && (ChangeMoveKey[1] != 0 || ChangeMoveKey[3] != 0)))
	{
		if ((ChangeMoveKey[1] != 0 && MoveKey[3] != 0) || (ChangeMoveKey[3] != 0 && MoveKey[1] != 0))
		{
			CurState->ThrowState(USprintEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(URunLoopState::GetInstance());
		}
	}
	else
	{
		if ((ChangeMoveKey[0] != 0 && MoveKey[2] != 0) || (ChangeMoveKey[2] != 0 && MoveKey[0] != 0))
		{
			CurState->ThrowState(USprintEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(URunLoopState::GetInstance());
		}
		if ((ChangeMoveKey[1] != 0 && MoveKey[3] != 0) || (ChangeMoveKey[3] != 0 && MoveKey[1] != 0))
		{
			CurState->ThrowState(USprintEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(URunLoopState::GetInstance());
		}
	}
}

void USprintLoopState::Exit(IBaseGameEntity* CurState)
{
	CurState->ThrowState(USprintEndState::GetInstance());
	CurState->bIsEnd = true;
}
#pragma endregion USprintLoopState
#pragma region USprintEndState
USprintEndState* USprintEndState::GetInstance()
{
	static USprintEndState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USprintEndState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USprintEndState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Sprint_End);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void USprintEndState::Execute(IBaseGameEntity* CurState)
{
	// if(CurState->PlayTime >= 1.2f)
	// {
	// 	CurState->Irene->ActionEndChangeMoveState();
	// 	if(CurState->Irene->IreneState->IsSprintState())
	// 		CurState->Irene->ChangeStateAndLog(URunLoopState::GetInstance());
	// }
}

void USprintEndState::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAnim->SetSprintStateAnim(false);
	CurState->Irene->IreneAnim->SetSprintStopAnim(false);
	//CurState->Irene->SetCameraLagTime(0);
	//CurState->Irene->SetLastLagTime(CurState->Irene->SpringArmComp->CameraLagSpeed);
	if(CurState->Irene->CameraLagCurve.Num()>0)
	{
		CurState->Irene->SpringArmComp->CameraLagSpeed = 10;
		CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[9]);
	}
	CurState->bIsEnd = true;
}
#pragma endregion USprintEndState
#pragma endregion SprintState

#pragma region DodgeState
#pragma region UDodgeStartState
UDodgeStartState* UDodgeStartState::GetInstance()
{
	static UDodgeStartState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UDodgeStartState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UDodgeStartState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Dodge_Start);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	//CurState->Irene->GetMesh()->SetVisibility(false);
	CurState->Irene->Weapon->SetVisibility(false);
	//CurState->Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerDodge"));
	//CurState->Irene->GetCharacterMovement()->BrakingFrictionFactor = 0;
	//CurState->Irene->GetCharacterMovement()->BrakingDecelerationWalking = 0;
	//CurState->Irene->SetCameraLagTime(0);
	if(CurState->Irene->CameraLagCurve.Num()>0)
	{
		CurState->Irene->SpringArmComp->CameraLagSpeed = 30;
		CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[8]);
	}
	CurState->Irene->IreneData.IsSkipMonsterAttack = true;

	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
}

void UDodgeStartState::Execute(IBaseGameEntity* CurState)
{
	if (CurState->Irene->IreneInput->GetIsDialogOn())
	{
		CurState->ThrowState(UDodgeEndState::GetInstance());
		CurState->Irene->ChangeStateAndLog(UIdleState::GetInstance());
		CurState->Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	}
	
	//CurState->Irene->IreneInput->MoveAuto();

	// 일반 대쉬
	if(CurState->Irene->IreneAnim->GetDodgeDir() != 10)
	{
		if (CurState->PlayTime >= 0.24f)
		{
			const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
			if (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0)
			{
				CurState->ThrowState(UDodgeEndState::GetInstance());
				CurState->Irene->ChangeStateAndLog(USprintLoopState::GetInstance());
			}
			CurState->Irene->IreneInput->SetIsDodgeToDodge(true);
		}
		if (CurState->PlayTime >= 0.76f)
		{
			CurState->Irene->ChangeStateAndLog(UDodgeEndState::GetInstance());
		}
	}
	else
	{
		// 퍼펙트 닷지
		// 왼클릭으로 도중 끊기
		if(CurState->PlayTime >= 2.5f * CurState->Irene->IreneInput->GetSlowScale() * 0.6f && CurState->Irene->IreneInput->bLeftButtonPressed)
		{
			CurState->Irene->IreneAnim->SetDodgeDir(0);
			CurState->Irene->ActionEndChangeMoveState(true);
		}
		// 이동으로 도중 끊기
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->PlayTime >= 2.5f * CurState->Irene->IreneInput->GetSlowScale() * 0.8f && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			CurState->Irene->IreneAnim->SetDodgeDir(0);
			CurState->Irene->ChangeStateAndLog(USprintLoopState::GetInstance());
		}
		// 끝까지 재생
		if (CurState->PlayTime >= 2.5f * CurState->Irene->IreneInput->GetSlowScale())
		{
			CurState->Irene->IreneAnim->SetDodgeDir(0);
			CurState->Irene->ActionEndChangeMoveState(true);
		}
	}
}

void UDodgeStartState::Exit(IBaseGameEntity* CurState)
{
	CurState->ThrowState(UDodgeEndState::GetInstance());
	CurState->bIsEnd = true;
}
#pragma endregion UDodgeStartState
#pragma region UDodgeEndState
UDodgeEndState* UDodgeEndState::GetInstance()
{
	static UDodgeEndState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UDodgeEndState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UDodgeEndState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Dodge_End);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	
	//CurState->Irene->GetMesh()->SetVisibility(true);
	//CurState->Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	//CurState->Irene->GetCharacterMovement()->BrakingFrictionFactor = 2;
	//CurState->Irene->GetCharacterMovement()->BrakingDecelerationWalking = 2048;
	//CurState->Irene->GetCharacterMovement()->Velocity = FVector::ZeroVector;
	CurState->Irene->IreneData.IsSkipMonsterAttack = false;
	//CurState->Irene->SetCameraLagTime(0);
	//CurState->Irene->SetLastLagTime(CurState->Irene->SpringArmComp->CameraLagSpeed);
	if(CurState->Irene->CameraLagCurve.Num()>0)
	{
		CurState->Irene->SpringArmComp->CameraLagSpeed = 10;
		CurState->Irene->SetUseCameraLag(CurState->Irene->CameraLagCurve[9]);
	}
}

void UDodgeEndState::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->ActionEndChangeMoveState(true);
}

void UDodgeEndState::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->SetIsDodgeToDodge(false);
	CurState->bIsEnd = true;
}
#pragma endregion UDodgeEndState
#pragma endregion DodgeState

#pragma region JumpState
#pragma region UJumpStartState
UJumpStartState* UJumpStartState::GetInstance()
{
	static UJumpStartState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UJumpStartState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UJumpStartState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Jump_Start);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	//CurState->Irene->GetMovementComponent()->Velocity = CurState->Irene->GetMovementComponent()->Velocity / CurState->Irene->IreneData.JumpDrag;
	if (CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->Weapon->SetVisibility(false);
		CurState->Irene->WeaponVisible(false);
	}
	CurState->Irene->IreneData.IsAttacking = false;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.IsComboInputOn = false;
	CurState->Irene->IreneData.CurrentCombo = 0;
}

void UJumpStartState::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->ChangeStateAndLog(UJumpLoopState::GetInstance());
}

void UJumpStartState::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->GetCharacterMovement()->GravityScale = 1;
	CurState->bIsEnd = true;
}
#pragma endregion UJumpStartState
#pragma region UJumpLoopState
UJumpLoopState* UJumpLoopState::GetInstance()
{
	static UJumpLoopState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UJumpLoopState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UJumpLoopState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Jump_Loop);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurrentTime = 0;
	if (CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->Weapon->SetVisibility(false);
		CurState->Irene->WeaponVisible(false);
	}
}

void UJumpLoopState::Execute(IBaseGameEntity* CurState)
{
	CurrentTime = CurState->PlayTime;
	// 점프 상태 중 키입력에 따라 바닥에 도착할 경우 정지, 걷기, 달리기 상태 지정
	if (!CurState->Irene->GetCharacterMovement()->IsFalling())
	{
		if (CurState->Irene->IreneInput->MoveKey[0] > 2)
			CurState->Irene->IreneInput->MoveKey[0] -= 2;
		if (CurState->Irene->IreneInput->MoveKey[1] > 2)
			CurState->Irene->IreneInput->MoveKey[1] -= 2;
		if (CurState->Irene->IreneInput->MoveKey[2] > 2)
			CurState->Irene->IreneInput->MoveKey[2] -= 2;
		if (CurState->Irene->IreneInput->MoveKey[3] > 2)
			CurState->Irene->IreneInput->MoveKey[3] -= 2;

		if (CurState->Irene->IreneInput->MoveKey[0] == 0 && CurState->Irene->IreneInput->MoveKey[1] == 0 && CurState->Irene->IreneInput->MoveKey[2] == 0 && CurState->Irene->IreneInput->MoveKey[3] == 0)
		{
			CurState->Irene->ChangeStateAndLog(UJumpEndState::GetInstance());
		}
		else if (CurState->Irene->GetCharacterMovement()->MaxWalkSpeed >= CurState->Irene->IreneData.SprintMaxSpeed * CurState->Irene->IreneData.WaterDeBuffSpeed)
		{
			CurState->ThrowState(UJumpEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(USprintLoopState::GetInstance());
		}
		else
		{
			CurState->ThrowState(UJumpEndState::GetInstance());
			CurState->Irene->ChangeStateAndLog(URunLoopState::GetInstance());
		}
	}
}

void UJumpLoopState::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->GetCharacterMovement()->GravityScale = 1;
	CurState->bIsEnd = true;
}
#pragma endregion UJumpLoopState
#pragma region UJumpEndState
UJumpEndState* UJumpEndState::GetInstance()
{
	static UJumpEndState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UJumpEndState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UJumpEndState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Jump_End);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurState->Irene->GetCharacterMovement()->GravityScale = 1;
	CurState->Irene->GetCharacterMovement()->MaxWalkSpeed = CurState->Irene->IreneData.RunMaxSpeed * CurState->Irene->IreneData.WaterDeBuffSpeed;
}

void UJumpEndState::Execute(IBaseGameEntity* CurState)
{
	// if (CurState->Irene->IreneInput->GetFallingRoll() && !CurState->Irene->GetMovementComponent()->IsFalling())
	// {
	// 	// 공중에서 구르기 키 입력 이후 땅에 도착하면 구르기 실행
	// 	CurState->Irene->IreneInput->DodgeKeyword();
	// }
	if (CurState->PlayTime >= 0.6f)
	{
		CurState->Irene->ActionEndChangeMoveState();
	}
}

void UJumpEndState::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->GetCharacterMovement()->GravityScale = 1;
	CurState->Irene->IreneInput->SetFallingRoll(false);
	CurState->bIsEnd = true;
}
#pragma endregion UJumpEndState
#pragma endregion JumpState

#pragma region AttackState
#pragma region UBasicAttack1State
UBasicAttack1State* UBasicAttack1State::GetInstance()
{
	static UBasicAttack1State* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UBasicAttack1State>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UBasicAttack1State::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::B_Attack_1);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	
	CurState->Irene->IreneAttack->SetCameraShakeTime(0);
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[0]);
	StartShakeTime = 0.0f;	
	CurState->Irene->IreneData.CanNextCombo = false;
	
	CurState->Irene->IreneAttack->SetTrueAttackCount(1);

	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);
	
	if (!CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->GetMesh()->SetVisibility(true);
		CurState->Irene->Weapon->SetVisibility(true);
		CurState->Irene->WeaponVisible(true);
	}

	if(CurState->Irene->IreneAnim->GetCurrentActiveMontage() == nullptr)
	{
		CurState->Irene->IreneAnim->PlayAttackMontage();
	}
	
	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;

	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}

void UBasicAttack1State::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveAuto();

	if (CurState->Irene->IreneAnim->Montage_GetCurrentSection(CurState->Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack2")
		&& CurState->Irene->IreneState->GetStateToString().Compare(FString("B_Attack_2")) != 0 && CurState->Irene->IreneData.CurrentCombo == 2)
	{
		CurState->Irene->IreneAttack->SetAttackState();
	}
	
	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;

	// 이동 스킵
	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
	if(CurState->PlayTime >= EndTime)
	{
		EndTimeExit(CurState);
	}
}
void UBasicAttack1State::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void UBasicAttack1State::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAttack->AttackTimeEndState();
}
#pragma endregion UBasicAttack1State
#pragma region UBasicAttack2State
UBasicAttack2State* UBasicAttack2State::GetInstance()
{
	static UBasicAttack2State* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UBasicAttack2State>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UBasicAttack2State::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::B_Attack_2);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	
	CurState->Irene->IreneAttack->SetCameraShakeTime(0);
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[1]);
	StartShakeTime = 0.0f;
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.CurrentCombo = 2;
	
	CurState->Irene->IreneAttack->SetTrueAttackCount(2);
	
	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	if (!CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->GetMesh()->SetVisibility(true);
		CurState->Irene->Weapon->SetVisibility(true);
		CurState->Irene->WeaponVisible(true);
	}
	
	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;

	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());	
}
void UBasicAttack2State::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveAuto();
	if (CurState->Irene->IreneAnim->Montage_GetCurrentSection(CurState->Irene->IreneAnim->GetCurrentActiveMontage()) == FName("Attack3")
		&& CurState->Irene->IreneState->GetStateToString().Compare(FString("B_Attack_3")) != 0 && CurState->Irene->IreneData.CurrentCombo == 3)
	{
		CurState->Irene->IreneAttack->SetAttackState();
	}
	
	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;

	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
	if(CurState->PlayTime >= EndTime)
	{
		EndTimeExit(CurState);
	}
}
void UBasicAttack2State::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void UBasicAttack2State::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAttack->AttackTimeEndState();
}
#pragma endregion UBasicAttack2State
#pragma region UBasicAttack3State
UBasicAttack3State* UBasicAttack3State::GetInstance()
{
	static UBasicAttack3State* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UBasicAttack3State>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UBasicAttack3State::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::B_Attack_3);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	
	CurState->Irene->IreneAttack->SetCameraShakeTime(0);
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[2]);
	StartShakeTime = 0.0f;
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.CurrentCombo = 3;
	
	if(!CurState->Irene->bIsSpiritStance)
		CurState->Irene->IreneAttack->SetTrueAttackCount(3);
	else
		CurState->Irene->IreneAttack->SetTrueAttackCount(4);

	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	if (!CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->GetMesh()->SetVisibility(true);
		CurState->Irene->Weapon->SetVisibility(true);
		CurState->Irene->WeaponVisible(true);
	}

	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;
	
	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}
void UBasicAttack3State::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveAuto();

	CurState->Irene->IreneData.IsComboInputOn = false;

	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;

	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
	if(CurState->PlayTime >= EndTime)
	{
		EndTimeExit(CurState);
	}
}
void UBasicAttack3State::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void UBasicAttack3State::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneAttack->AttackTimeEndState();
}
#pragma endregion UBasicAttack3State
#pragma endregion AttackState

#pragma region Skill
#pragma region SwordSkill1
USwordSkill1* USwordSkill1::GetInstance()
{
	static USwordSkill1* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USwordSkill1>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USwordSkill1::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Sword_Skill_1);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[9]);
	StartShakeTime = 0.0f;
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = true;
	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	if (!CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->GetMesh()->SetVisibility(true);
		CurState->Irene->Weapon->SetVisibility(true);
		CurState->Irene->WeaponVisible(true);
	}

	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;

	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}

void USwordSkill1::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveAuto();
	
	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;
	
	// 이동 스킵
	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
	if(CurState->PlayTime >= EndTime)
	{
		EndTimeExit(CurState);
	}
}
void USwordSkill1::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void USwordSkill1::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->CameraShakeOn = false;
	CurState->Irene->IreneData.IsAttacking = false;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackTimeEndState();
	CurState->bIsEnd = true;
}
#pragma endregion SwordSkill1
#pragma region SwordSkill2
USwordSkill2* USwordSkill2::GetInstance()
{
	static USwordSkill2* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USwordSkill2>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USwordSkill2::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Sword_Skill_2);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[9]);
	StartShakeTime = 0.0f;
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = true;
	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	CurState->Irene->IreneInput->SetCanUseSecondSwordSkill(false);
	
	if (!CurState->Irene->Weapon->IsVisible())
	{
		CurState->Irene->GetMesh()->SetVisibility(true);
		CurState->Irene->Weapon->SetVisibility(true);
		CurState->Irene->WeaponVisible(true);
	}

	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;

	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}

void USwordSkill2::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->MoveAuto();
	
	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;
	
	// 이동 스킵
	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
	if(CurState->PlayTime >= EndTime)
	{
		EndTimeExit(CurState);
	}
}
void USwordSkill2::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void USwordSkill2::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->CameraShakeOn = false;
	CurState->Irene->IreneData.IsAttacking = false;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackTimeEndState();
	CurState->bIsEnd = true;
}
#pragma endregion SwordSkill2
#pragma region USpiritSkill1
USpiritSkill1* USpiritSkill1::GetInstance()
{
	static USpiritSkill1* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USpiritSkill1>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USpiritSkill1::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Spirit_Skill_1);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[11]);
	StartShakeTime = 0.0f;	
	
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.CurrentCombo = 1;

	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	CurState->Irene->IreneAttack->SetTrueAttackCount(1);	
	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time+0.1f;
	if(CurState->Irene->IreneSpirit != nullptr)
	{
		if(CurState->Irene->IreneSpirit->IreneSpiritAnim->GetCurrentActiveMontage() != nullptr)
			EndTime+=0.1f;
		CurState->Irene->IreneSpirit->DestroySpiritTimer(EndTime);
	}
	
	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}
void USpiritSkill1::Execute(IBaseGameEntity* CurState)
{	
	// 몽타주 시간
	if (CurState->PlayTime >= EndTime)
	{
		if(CurState->Irene->IreneSpirit != nullptr)
			CurState->Irene->IreneSpirit->DestroySpirit();
		EndTimeExit(CurState);
	}

	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;
	
	// 이동 스킵
	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			STARRYLOG_S(Warning);
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
}
void USpiritSkill1::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void USpiritSkill1::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->CameraShakeOn = false;
	CurState->Irene->IreneData.IsAttacking = false;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackTimeEndState();
	CurState->bIsEnd = true;
}
#pragma endregion USpiritSkill1
#pragma region USpiritSkill2
USpiritSkill2* USpiritSkill2::GetInstance()
{
	static USpiritSkill2* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USpiritSkill2>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USpiritSkill2::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Spirit_Skill_2);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[11]);
	StartShakeTime = 0.0f;
	
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.CurrentCombo = 2;

	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));

	CurState->Irene->IreneAttack->SetTrueAttackCount(2);
	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;
	if(CurState->Irene->IreneSpirit != nullptr)
		CurState->Irene->IreneSpirit->DestroySpiritTimer(EndTime);
	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}
void USpiritSkill2::Execute(IBaseGameEntity* CurState)
{	
	// 몽타주 시간
	if (CurState->PlayTime >= EndTime)
	{
		if(CurState->Irene->IreneSpirit != nullptr)
			CurState->Irene->IreneSpirit->DestroySpirit();
		EndTimeExit(CurState);
	}

	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;
	
	// 이동 스킵
	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
}
void USpiritSkill2::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void USpiritSkill2::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->CameraShakeOn = false;
	CurState->Irene->IreneData.IsAttacking = false;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackTimeEndState();
	CurState->bIsEnd = true;
}
#pragma endregion USpiritSkill2
#pragma region USpiritSkill3
USpiritSkill3* USpiritSkill3::GetInstance()
{
	static USpiritSkill3* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USpiritSkill3>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USpiritSkill3::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Spirit_Skill_3);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	if(CurState->Irene->CameraLagCurve.Num()>0)
		CurState->Irene->SetUseShakeCurve(CurState->Irene->CameraShakeCurve[11]);
	StartShakeTime = 0.0f;
	
	CurState->Irene->IreneData.IsAttacking = true;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneData.CurrentCombo = 3;

	CurState->Irene->IreneInput->SetNextAttack(false);
	CurState->Irene->IreneInput->SetJumpAttack(false);
	CurState->Irene->IreneInput->SetReAttack(false);
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillSkip(false);
	CurState->Irene->IreneAttack->SetCanSkillToAttack(false);

	const FVector IrenePosition = CurState->Irene->GetActorLocation();
	const float Z = UKismetMathLibrary::FindLookAtRotation(IrenePosition,IrenePosition + CurState->Irene->IreneInput->GetMoveKeyToDirVector()).Yaw;
	CurState->Irene->SetActorRotation(FRotator(0.0f, Z, 0.0f));
	
	CurState->Irene->IreneAttack->SetTrueAttackCount(3);
	const TUniquePtr<FAttackDataTable> AttackTable = MakeUnique<FAttackDataTable>(*CurState->Irene->IreneAttack->GetNameAtAttackDataTable(CurState->Irene->IreneAttack->GetBasicAttackDataTableName()));
	EndTime = AttackTable->C_Time;
	
	if(CurState->Irene->IreneSpirit != nullptr)
		CurState->Irene->IreneSpirit->DestroySpiritTimer(EndTime);
	
	CurState->Irene->IreneAttack->SetDamageBeforeTableName(CurState->Irene->IreneAttack->GetBasicAttackDataTableName().ToString());
}
void USpiritSkill3::Execute(IBaseGameEntity* CurState)
{	
	// 몽타주 시간
	if (CurState->PlayTime >= EndTime)
	{
		if(CurState->Irene->IreneSpirit != nullptr)
			CurState->Irene->IreneSpirit->DestroySpirit();
		EndTimeExit(CurState);
	}

	if (CurState->Irene->CameraShakeOn == true && StartShakeTime == 0)
		StartShakeTime = CurState->PlayTime;
	if (StartShakeTime != 0 && CurState->PlayTime >= StartShakeTime + 0.2f)
		CurState->Irene->CameraShakeOn = false;
	
	// 이동 스킵
	if (CurState->Irene->IreneData.IsAttacking)
	{
		const TArray<uint8> MoveKey = CurState->Irene->IreneInput->MoveKey;
		if (CurState->Irene->IreneAttack->GetCanMoveSkip() && (MoveKey[0] != 0 || MoveKey[1] != 0 || MoveKey[2] != 0 || MoveKey[3] != 0))
		{
			if (CurState->Irene->Weapon->IsVisible())
			{
				CurState->Irene->Weapon->SetVisibility(false);
				CurState->Irene->WeaponVisible(false);
			}
			CurState->Irene->IreneAnim->StopAllMontages(0);
			CurState->Irene->ActionEndChangeMoveState();
		}
	}
}
void USpiritSkill3::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackEndComboState();
	CurState->Irene->CameraShakeOn = false;
	CurState->bIsEnd = true;
}
void USpiritSkill3::EndTimeExit(IBaseGameEntity* CurState)
{
	CurState->Irene->CameraShakeOn = false;
	CurState->Irene->IreneData.IsAttacking = false;
	CurState->Irene->IreneData.CanNextCombo = false;
	CurState->Irene->IreneInput->SetAttackUseSkill(false);
	CurState->Irene->IreneAttack->AttackTimeEndState();
	CurState->bIsEnd = true;
}
#pragma endregion USpiritSkill3
#pragma endregion Skill

#pragma region FormChangeState
UFormChangeState* UFormChangeState::GetInstance()
{
	static UFormChangeState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UFormChangeState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UFormChangeState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Form_Change);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UFormChangeState::Execute(IBaseGameEntity* CurState)
{

}

void UFormChangeState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion FormChangeState

#pragma region Hit
#pragma region UHit1State
UHit1State* UHit1State::GetInstance()
{
	static UHit1State* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UHit1State>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UHit1State::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Hit_1);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
    CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
}

void UHit1State::Execute(IBaseGameEntity* CurState)
{	
	if (CurState->PlayTime >= 0.56f)
	{
		CurState->Irene->ActionEndChangeMoveState();
	}
}

void UHit1State::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion UHit1State
#pragma region UHit2State
UHit2State* UHit2State::GetInstance()
{
	static UHit2State* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UHit2State>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UHit2State::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Hit_2);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
	CurState->Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerDodge"));
}

void UHit2State::Execute(IBaseGameEntity* CurState)
{
	if(CurState->PlayTime > CurState->Irene->GetWorld()->DeltaTimeSeconds)
	{
		CurState->Irene->ChangeStateAndLog(UHit1State::GetInstance());
	}
	//CurState->Irene->IreneInput->MoveForward();
	//CurState->Irene->IreneInput->MoveRight();
}

void UHit2State::Exit(IBaseGameEntity* CurState)
{
	CurState->Irene->GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	CurState->bIsEnd = true;
}
#pragma endregion UHit2State
#pragma region UKnockBackState
UKnockBackState* UKnockBackState::GetInstance()
{
	static UKnockBackState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UKnockBackState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UKnockBackState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::KnockBack);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurState->Irene->IreneAttack->SetCanMoveSkip(false);
	CurState->Irene->IreneAttack->SetCanDodgeJumpSkip(false);
}

void UKnockBackState::Execute(IBaseGameEntity* CurState)
{
	CurState->Irene->ActionEndChangeMoveState();
}

void UKnockBackState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion UKnockBackState
#pragma endregion Hit

#pragma region DeathState
UDeathState* UDeathState::GetInstance()
{
	static UDeathState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UDeathState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UDeathState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Death);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	CurState->Irene->IreneAnim->StopAllMontages(0);
	CurState->Irene->IreneAnim->SetDeadAnim(true);
}

void UDeathState::Execute(IBaseGameEntity* CurState)
{

}

void UDeathState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion DeathState

#pragma region IsState
bool UIreneFSM::IsIdleState()const
{
	if (StateEnumValue == EStateEnum::Idle || StateEnumValue == EStateEnum::BattleIdle)
		return true;
	return false;
}
bool UIreneFSM::IsRunState()const
{
	if (StateEnumValue == EStateEnum::Run_Loop || StateEnumValue == EStateEnum::Run_End)
		return true;
	return false;
}
bool UIreneFSM::IsSprintState()const
{
	if (StateEnumValue == EStateEnum::Sprint_Loop || StateEnumValue == EStateEnum::Sprint_End)
		return true;
	return false;
}
bool UIreneFSM::IsDodgeState()const
{
	if (StateEnumValue == EStateEnum::Dodge_Start || StateEnumValue == EStateEnum::Dodge_End)
		return true;
	return false;
}
bool UIreneFSM::IsJumpState()const
{
	if (StateEnumValue == EStateEnum::Jump_Start || StateEnumValue == EStateEnum::Jump_Loop || StateEnumValue == EStateEnum::Jump_End)
		return true;
	return false;
}
bool UIreneFSM::IsAttackState()const
{
	if (StateEnumValue == EStateEnum::B_Attack_1 || StateEnumValue == EStateEnum::B_Attack_2 || StateEnumValue == EStateEnum::B_Attack_3)
		return true;
	return false;
}
bool UIreneFSM::IsSkillState() const
{
	if (StateEnumValue == EStateEnum::Sword_Skill_1 || StateEnumValue == EStateEnum::Sword_Skill_2 ||
		StateEnumValue == EStateEnum::Spirit_Skill_1 || StateEnumValue == EStateEnum::Spirit_Skill_2 || StateEnumValue == EStateEnum::Spirit_Skill_3)
		return true;
	return false;
}
bool UIreneFSM::IsFormChangeState()const
{
	if (StateEnumValue == EStateEnum::Form_Change)
		return true;
	return false;
}
bool UIreneFSM::IsHitState()const
{
	if (StateEnumValue == EStateEnum::Hit_1 || StateEnumValue == EStateEnum::Hit_2 || StateEnumValue == EStateEnum::KnockBack)
		return true;
	return false;
}
bool UIreneFSM::IsDeathState()const
{
	if (StateEnumValue == EStateEnum::Death)
		return true;
	return false;
}
#pragma endregion IsState

#pragma region FindState
bool UIreneFSM::IsFirstAttack()const
{
	if (StateEnumValue == EStateEnum::B_Attack_1)
		return true;
	return false;
}
bool UIreneFSM::IsSecondAttack() const
{
	if (StateEnumValue == EStateEnum::B_Attack_2)
		return true;
	return false;
}
bool UIreneFSM::IsThirdAttack() const
{
	if (StateEnumValue == EStateEnum::B_Attack_3)
		return true;
	return false;
}
bool UIreneFSM::IsKnockBackState() const
{
	if (StateEnumValue == EStateEnum::KnockBack)
		return true;
	return false;
}
#pragma endregion  FindState