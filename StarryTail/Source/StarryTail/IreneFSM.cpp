// Fill out your copyright notice in the Description page of Project Settings.

#include "IreneFSM.h"

#pragma region IreneFSM
void IreneFSM::Update(float value)
{
	this->PlayTime += value;
	StateValue->Execute(this);
}
void IreneFSM::ChangeState(State* newState)
{
	StateValue->Exit(this);
	StateValue = newState;
	StateValue->Enter(this);
}
bool IreneFSM::CanIdle()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		//StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		StateEnumValue == StateEnum::Jump ||
		StateEnumValue == StateEnum::Fall ||
		StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanDeath()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		StateEnumValue == StateEnum::Jump ||
		StateEnumValue == StateEnum::Fall ||
		StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanDodge()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd)
		StateEnumValue == StateEnum::Jump ||
		StateEnumValue == StateEnum::Fall ||
		StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanHit()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd)
		StateEnumValue == StateEnum::Jump ||
		StateEnumValue == StateEnum::Fall ||
		StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanBasicAttack()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint ||
		StateEnumValue == StateEnum::SprintEnd)
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanActionAttack()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint ||
		StateEnumValue == StateEnum::SprintEnd)
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanBattleIdle()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack)
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

bool IreneFSM::CanRun()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanSprint()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run)
		//StateEnumValue == StateEnum::Sprint ||
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanSprintEnd()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		//StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanJump()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanFall()
{
	if (StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		StateEnumValue == StateEnum::BasicAttack ||
		StateEnumValue == StateEnum::ActionAttack ||
		StateEnumValue == StateEnum::BattleIdle ||
		StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint ||
		StateEnumValue == StateEnum::SprintEnd ||
		StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

bool IreneFSM::CanSprintJump()
{
	if (//StateEnumValue == StateEnum::Idle ||
		//StateEnumValue == StateEnum::Death ||
		//StateEnumValue == StateEnum::Dodge ||
		//StateEnumValue == StateEnum::Hit ||
		//StateEnumValue == StateEnum::BasicAttack ||
		//StateEnumValue == StateEnum::ActionAttack ||
		//StateEnumValue == StateEnum::BattleIdle ||
		//StateEnumValue == StateEnum::Run ||
		StateEnumValue == StateEnum::Sprint)
		//StateEnumValue == StateEnum::SprintEnd ||
		//StateEnumValue == StateEnum::Jump ||
		//StateEnumValue == StateEnum::Fall ||
		//StateEnumValue == StateEnum::SprintJump)
		return true;
	else
		return false;
}

FString IreneFSM::getStateToString()
{
	switch (StateEnumValue)
	{
	case StateEnum::Idle: return FString("Idle");
	case StateEnum::Death: return FString("Death");
	case StateEnum::Dodge: return FString("Dodge");
	case StateEnum::Hit: return FString("Hit");
	case StateEnum::BasicAttack: return FString("BasicAttack");
	case StateEnum::ActionAttack: return FString("BasicAttack");
	case StateEnum::BattleIdle: return FString("BattleIdle");
	case StateEnum::Run: return FString("Run");
	case StateEnum::Sprint: return FString("Sprint");
	case StateEnum::SprintEnd: return FString("SprintEnd");
	case StateEnum::Jump: return FString("Jump");
	case StateEnum::Fall: return FString("Fall");
	case StateEnum::SprintJump: return FString("SprintJump");
	default: return FString("Error StateEnumToString");
	}
}
#pragma endregion IreneFSM

#pragma region StateInterface
BaseGameEntity::BaseGameEntity() :PlayTime(0.0f), bIsEnd(false)
{

}
#pragma endregion StateInterface
#pragma region IdleState
IdleState* IdleState::getInstance()
{
	static IdleState* instance;
	if (instance == nullptr)
		instance = new IdleState();
	return instance;
}

void IdleState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Idle);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void IdleState::Execute(BaseGameEntity* curState)
{

}

void IdleState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion IdleState
#pragma region DeathState
DeathState* DeathState::getInstance()
{
	static DeathState* instance;
	if (instance == nullptr)
		instance = new DeathState();
	return instance;
}

void DeathState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Death);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void DeathState::Execute(BaseGameEntity* curState)
{

}

void DeathState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion DeathState
#pragma region DodgeState
DodgeState* DodgeState::getInstance()
{
	static DodgeState* instance;
	if (instance == nullptr)
		instance = new DodgeState();
	return instance;
}

void DodgeState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Dodge);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void DodgeState::Execute(BaseGameEntity* curState)
{

}

void DodgeState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion DodgeState
#pragma region HitState
HitState* HitState::getInstance()
{
	static HitState* instance;
	if (instance == nullptr)
		instance = new HitState();
	return instance;
}

void HitState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Hit);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void HitState::Execute(BaseGameEntity* curState)
{

}

void HitState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion HitState
#pragma region BasicAttackState
BasicAttackState* BasicAttackState::getInstance()
{
	static BasicAttackState* instance;
	if (instance == nullptr)
		instance = new BasicAttackState();
	return instance;
}

void BasicAttackState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::BasicAttack);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void BasicAttackState::Execute(BaseGameEntity* curState)
{

}

void BasicAttackState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion BasicAttackState
#pragma region ActionAttackState
ActionAttackState* ActionAttackState::getInstance()
{
	static ActionAttackState* instance;
	if (instance == nullptr)
		instance = new ActionAttackState();
	return instance;
}

void ActionAttackState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::ActionAttack);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void ActionAttackState::Execute(BaseGameEntity* curState)
{

}

void ActionAttackState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion ActionAttackState
#pragma region BattleIdleState
BattleIdleState* BattleIdleState::getInstance()
{
	static BattleIdleState* instance;
	if (instance == nullptr)
		instance = new BattleIdleState();
	return instance;
}

void BattleIdleState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::BattleIdle);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void BattleIdleState::Execute(BaseGameEntity* curState)
{

}

void BattleIdleState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion BattleIdleState
#pragma region RunState
RunState* RunState::getInstance()
{
	static RunState* instance;
	if (instance == nullptr)
		instance = new RunState();
	return instance;
}

void RunState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Run);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void RunState::Execute(BaseGameEntity* curState)
{

}

void RunState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion RunState
#pragma region SprintState
SprintState* SprintState::getInstance()
{
	static SprintState* instance;
	if (instance == nullptr)
		instance = new SprintState();
	return instance;
}

void SprintState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Sprint);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void SprintState::Execute(BaseGameEntity* curState)
{

}

void SprintState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion SprintState
#pragma region SprintEndState
SprintEndState* SprintEndState::getInstance()
{
	static SprintEndState* instance;
	if (instance == nullptr)
		instance = new SprintEndState();
	return instance;
}

void SprintEndState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::SprintEnd);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void SprintEndState::Execute(BaseGameEntity* curState)
{

}

void SprintEndState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion SprintEndState
#pragma region JumpState
JumpState* JumpState::getInstance()
{
	static JumpState* instance;
	if (instance == nullptr)
		instance = new JumpState();
	return instance;
}

void JumpState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Jump);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void JumpState::Execute(BaseGameEntity* curState)
{

}

void JumpState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion JumpState
#pragma region FallState
FallState* FallState::getInstance()
{
	static FallState* instance;
	if (instance == nullptr)
		instance = new FallState();
	return instance;
}

void FallState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Fall);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void FallState::Execute(BaseGameEntity* curState)
{

}

void FallState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion FallState
#pragma region SprintJumpState
SprintJumpState* SprintJumpState::getInstance()
{
	static SprintJumpState* instance;
	if (instance == nullptr)
		instance = new SprintJumpState();
	return instance;
}

void SprintJumpState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::SprintJump);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void SprintJumpState::Execute(BaseGameEntity* curState)
{

}

void SprintJumpState::Exit(BaseGameEntity* curState)
{
	curState->bIsEnd = true;
}
#pragma endregion SprintJumpState