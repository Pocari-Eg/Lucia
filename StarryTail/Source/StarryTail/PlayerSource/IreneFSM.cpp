// Fill out your copyright notice in the Description page of Project Settings.

#include "IreneFSM.h"

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
bool UIreneFSM::CanIdle()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == EStateEnum::Dodge ||
		StateEnumValue == EStateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		//StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		StateEnumValue == EStateEnum::Jump ||
		StateEnumValue == EStateEnum::Fall ||
		StateEnumValue == EStateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanDeath()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == EStateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		StateEnumValue == EStateEnum::Jump ||
		StateEnumValue == EStateEnum::Fall ||
		StateEnumValue == EStateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanDodge()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd)
		StateEnumValue == EStateEnum::Jump ||
		StateEnumValue == EStateEnum::Fall ||
		StateEnumValue == EStateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanHit()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd)
		StateEnumValue == EStateEnum::Jump ||
		StateEnumValue == EStateEnum::Fall ||
		StateEnumValue == EStateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanBasicAttack()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == EStateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint ||
		StateEnumValue == EStateEnum::SprintEnd)
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanActionAttack()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint ||
		StateEnumValue == EStateEnum::SprintEnd)
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanBattleIdle()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == EStateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack)
		//StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		//StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanRun()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == EStateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanSprint()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == EStateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run)
		//StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanSprintEnd()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		//StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanJump()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanFall()
{
	if (StateEnumValue == EStateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == EStateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == EStateEnum::BasicAttack ||
		StateEnumValue == EStateEnum::ActionAttack ||
		StateEnumValue == EStateEnum::BattleIdle ||
		StateEnumValue == EStateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint ||
		StateEnumValue == EStateEnum::SprintEnd ||
		StateEnumValue == EStateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		StateEnumValue == EStateEnum::SprintJump)
		return true;
	else
		return false;
}

bool UIreneFSM::CanSprintJump()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		//StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		StateEnumValue == EStateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

FString UIreneFSM::GetStateToString() const
{
	switch (StateEnumValue)
	{
	case EStateEnum::Idle: return FString("Idle");
	case EStateEnum::Death: return FString("Death");
	case EStateEnum::Dodge: return FString("Dodge");
	case EStateEnum::Hit: return FString("Hit");
	case EStateEnum::BasicAttack: return FString("BasicAttack");
	case EStateEnum::ActionAttack: return FString("BasicAttack");
	case EStateEnum::BattleIdle: return FString("BattleIdle");
	case EStateEnum::Run: return FString("Run");
	case EStateEnum::Sprint: return FString("Sprint");
	case EStateEnum::SprintEnd: return FString("SprintEnd");
	case EStateEnum::Jump: return FString("Jump");
	case EStateEnum::Fall: return FString("Fall");
	case EStateEnum::SprintJump: return FString("SprintJump");
	default: return FString("Error StateEnumToString");
	}
}
#pragma endregion IreneFSM

#pragma region StateInterface

#pragma endregion StateInterface

#pragma region IdleState
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
}

void UIdleState::Execute(IBaseGameEntity* CurState)
{

}

void UIdleState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion IdleState
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
}

void UDeathState::Execute(IBaseGameEntity* CurState)
{

}

void UDeathState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion DeathState
#pragma region DodgeState
UDodgeState* UDodgeState::GetInstance()
{
	static UDodgeState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UDodgeState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UDodgeState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Dodge);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UDodgeState::Execute(IBaseGameEntity* CurState)
{

}

void UDodgeState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion DodgeState
#pragma region HitState
UHitState* UHitState::GetInstance()
{
	static UHitState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UHitState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UHitState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Hit);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UHitState::Execute(IBaseGameEntity* CurState)
{

}

void UHitState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion HitState
#pragma region BasicAttackState
UBasicAttackState* UBasicAttackState::GetInstance()
{
	static UBasicAttackState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UBasicAttackState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UBasicAttackState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::BasicAttack);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UBasicAttackState::Execute(IBaseGameEntity* CurState)
{

}

void UBasicAttackState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion BasicAttackState
#pragma region ActionAttackState
UActionAttackState* UActionAttackState::GetInstance()
{
	static UActionAttackState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UActionAttackState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UActionAttackState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::ActionAttack);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UActionAttackState::Execute(IBaseGameEntity* CurState)
{

}

void UActionAttackState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion ActionAttackState
#pragma region BattleIdleState
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

}

void UBattleIdleState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion BattleIdleState
#pragma region RunState
URunState* URunState::GetInstance()
{
	static URunState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<URunState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void URunState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Run);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void URunState::Execute(IBaseGameEntity* CurState)
{

}

void URunState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion RunState
#pragma region SprintState
USprintState* USprintState::GetInstance()
{
	static USprintState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USprintState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USprintState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Sprint);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void USprintState::Execute(IBaseGameEntity* CurState)
{

}

void USprintState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion SprintState
#pragma region SprintEndState
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
	CurState->SetStateEnum(EStateEnum::SprintEnd);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void USprintEndState::Execute(IBaseGameEntity* CurState)
{

}

void USprintEndState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion SprintEndState
#pragma region JumpState
UJumpState* UJumpState::GetInstance()
{
	static UJumpState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UJumpState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void UJumpState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Jump);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UJumpState::Execute(IBaseGameEntity* CurState)
{

}

void UJumpState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion JumpState
#pragma region FallState
UFallState* UFallState::GetInstance()
{
	static UFallState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<UFallState>();
		Instance->AddToRoot();
	}
	
	return Instance;
}
void UFallState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Fall);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void UFallState::Execute(IBaseGameEntity* CurState)
{

}

void UFallState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion FallState
#pragma region SprintJumpState
USprintJumpState* USprintJumpState::GetInstance()
{
	static USprintJumpState* Instance;
	if (Instance == nullptr) {
		Instance = NewObject<USprintJumpState>();
		Instance->AddToRoot();
	}
	return Instance;
}
void USprintJumpState::Enter(IBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::SprintJump);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void USprintJumpState::Execute(IBaseGameEntity* CurState)
{

}

void USprintJumpState::Exit(IBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion SprintJumpState