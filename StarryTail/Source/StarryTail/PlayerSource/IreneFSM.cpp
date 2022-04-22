// Fill out your copyright notice in the Description page of Project Settings.

#include "IreneFSM.h"

#pragma region IreneFSM
void FIreneFSM::Update(const float Value)
{
	this->PlayTime += Value;
	StateValue->Execute(this);
}
void FIreneFSM::ChangeState(FState* NewState)
{
	StateValue->Exit(this);
	StateValue = NewState;
	StateValue->Enter(this);
}
bool FIreneFSM::CanIdle()
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

bool FIreneFSM::CanDeath()
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

bool FIreneFSM::CanDodge()
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

bool FIreneFSM::CanHit()
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

bool FIreneFSM::CanBasicAttack()
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

bool FIreneFSM::CanActionAttack()
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

bool FIreneFSM::CanBattleIdle()
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

bool FIreneFSM::CanRun()
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

bool FIreneFSM::CanSprint()
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

bool FIreneFSM::CanSprintEnd()
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

bool FIreneFSM::CanJump()
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

bool FIreneFSM::CanFall()
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

bool FIreneFSM::CanSprintJump()
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

FString FIreneFSM::GetStateToString() const
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
FBaseGameEntity::FBaseGameEntity(FPlayerCharacterDataStruct* Value) :PlayTime(0.0f), bIsEnd(false), CharacterDataStruct(Value)
{

}
#pragma endregion StateInterface
#pragma region IdleState
FIdleState* FIdleState::GetInstance()
{
	static FIdleState* Instance;
	if (Instance == nullptr)
		Instance = new FIdleState();
	return Instance;
}

void FIdleState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Idle);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
	HpTime = 0.0f;
	BeforeTime = 0.0f;
}

void FIdleState::Execute(FBaseGameEntity* CurState)
{
	const float DeltaTime = CurState->PlayTime - BeforeTime;
	HpTime += DeltaTime;
	if(HpTime > 2)
	{
		HpTime -= 2;
		//CurState->CharacterDataStruct->CurrentHP += 100;
	}
	BeforeTime = CurState->PlayTime;
}

void FIdleState::Exit(FBaseGameEntity* CurState)
{
	HpTime = 0.0f;
	BeforeTime = 0.0f;
	CurState->bIsEnd = true;
}
#pragma endregion IdleState
#pragma region DeathState
FDeathState* FDeathState::GetInstance()
{
	static FDeathState* Instance;
	if (Instance == nullptr)
		Instance = new FDeathState();
	return Instance;
}

void FDeathState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Death);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FDeathState::Execute(FBaseGameEntity* CurState)
{

}

void FDeathState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion DeathState
#pragma region DodgeState
FDodgeState* FDodgeState::GetInstance()
{
	static FDodgeState* Instance;
	if (Instance == nullptr)
		Instance = new FDodgeState();
	return Instance;
}

void FDodgeState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Dodge);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FDodgeState::Execute(FBaseGameEntity* CurState)
{

}

void FDodgeState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion DodgeState
#pragma region HitState
FHitState* FHitState::GetInstance()
{
	static FHitState* Instance;
	if (Instance == nullptr)
		Instance = new FHitState();
	return Instance;
}

void FHitState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Hit);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FHitState::Execute(FBaseGameEntity* CurState)
{

}

void FHitState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion HitState
#pragma region BasicAttackState
FBasicAttackState* FBasicAttackState::GetInstance()
{
	static FBasicAttackState* Instance;
	if (Instance == nullptr)
		Instance = new FBasicAttackState();
	return Instance;
}

void FBasicAttackState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::BasicAttack);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FBasicAttackState::Execute(FBaseGameEntity* CurState)
{

}

void FBasicAttackState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion BasicAttackState
#pragma region ActionAttackState
FActionAttackState* FActionAttackState::GetInstance()
{
	static FActionAttackState* Instance;
	if (Instance == nullptr)
		Instance = new FActionAttackState();
	return Instance;
}

void FActionAttackState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::ActionAttack);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FActionAttackState::Execute(FBaseGameEntity* CurState)
{

}

void FActionAttackState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion ActionAttackState
#pragma region BattleIdleState
FBattleIdleState* FBattleIdleState::GetInstance()
{
	static FBattleIdleState* Instance;
	if (Instance == nullptr)
		Instance = new FBattleIdleState();
	return Instance;
}

void FBattleIdleState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::BattleIdle);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FBattleIdleState::Execute(FBaseGameEntity* CurState)
{

}

void FBattleIdleState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion BattleIdleState
#pragma region RunState
FRunState* FRunState::GetInstance()
{
	static FRunState* Instance;
	if (Instance == nullptr)
		Instance = new FRunState();
	return Instance;
}

void FRunState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Run);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FRunState::Execute(FBaseGameEntity* CurState)
{

}

void FRunState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion RunState
#pragma region SprintState
FSprintState* FSprintState::GetInstance()
{
	static FSprintState* Instance;
	if (Instance == nullptr)
		Instance = new FSprintState();
	return Instance;
}

void FSprintState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Sprint);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FSprintState::Execute(FBaseGameEntity* CurState)
{

}

void FSprintState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion SprintState
#pragma region SprintEndState
FSprintEndState* FSprintEndState::GetInstance()
{
	static FSprintEndState* Instance;
	if (Instance == nullptr)
		Instance = new FSprintEndState();
	return Instance;
}

void FSprintEndState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::SprintEnd);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FSprintEndState::Execute(FBaseGameEntity* CurState)
{

}

void FSprintEndState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion SprintEndState
#pragma region JumpState
FJumpState* FJumpState::GetInstance()
{
	static FJumpState* Instance;
	if (Instance == nullptr)
		Instance = new FJumpState();
	return Instance;
}

void FJumpState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Jump);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FJumpState::Execute(FBaseGameEntity* CurState)
{

}

void FJumpState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion JumpState
#pragma region FallState
FFallState* FFallState::GetInstance()
{
	static FFallState* Instance;
	if (Instance == nullptr)
		Instance = new FFallState();
	return Instance;
}

void FFallState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::Fall);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FFallState::Execute(FBaseGameEntity* CurState)
{

}

void FFallState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion FallState
#pragma region SprintJumpState
FSprintJumpState* FSprintJumpState::GetInstance()
{
	static FSprintJumpState* Instance;
	if (Instance == nullptr)
		Instance = new FSprintJumpState();
	return Instance;
}

void FSprintJumpState::Enter(FBaseGameEntity* CurState)
{
	CurState->SetStateEnum(EStateEnum::SprintJump);
	CurState->PlayTime = 0.0f;
	CurState->bIsEnd = false;
}

void FSprintJumpState::Execute(FBaseGameEntity* CurState)
{

}

void FSprintJumpState::Exit(FBaseGameEntity* CurState)
{
	CurState->bIsEnd = true;
}
#pragma endregion SprintJumpState