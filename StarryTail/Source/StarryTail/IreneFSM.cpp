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

FString IreneFSM::getStateToString()
{
	switch (StateEnumValue)
	{
	case StateEnum::Idle: return FString("Idle");
	case StateEnum::AttackIdle: return FString("AttackIdle");
	case StateEnum::Run: return FString("Run");
	case StateEnum::Sprint: return FString("Sprint");
	case StateEnum::Dodge: return FString("Dodge");
	case StateEnum::Jump: return FString("Jump");
	case StateEnum::Fall: return FString("Fall");
	case StateEnum::Attack: return FString("Attack");
	case StateEnum::Hit: return FString("Hit");
	case StateEnum::Death: return FString("Death");
	default: return FString("Error StateEnumToString");
	}
}
const char* IreneFSM::StateEnumToString(StateEnum s)
{
    switch(s)
    {
    case StateEnum::Idle: return "Idle";
    case StateEnum::AttackIdle: return "AttackIdle";
    case StateEnum::Run: return "Run";
	case StateEnum::Sprint: return "Sprint";
    case StateEnum::Dodge: return "Dodge";
    case StateEnum::Jump: return "Jump";
	case StateEnum::Fall: return "Fall";
    case StateEnum::Attack: return "Attack";
    case StateEnum::Hit: return "Hit";
    case StateEnum::Death: return "Death";
    default: return "Error StateEnumToString";
    }
}
#pragma endregion IreneFSM

#pragma region StateInterface
BaseGameEntity::BaseGameEntity():PlayTime(0.0f), bIsEnd(false)
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
#pragma region AttackIdleState
AttackIdleState* AttackIdleState::getInstance()
{
	static AttackIdleState* instance;
	if (instance == nullptr)
		instance = new AttackIdleState();
	return instance;
}

void AttackIdleState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::AttackIdle);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void AttackIdleState::Execute(BaseGameEntity* curState)
{

}

void AttackIdleState::Exit(BaseGameEntity* curState)
{

}
#pragma endregion AttackIdleState
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

}
#pragma endregion SprintState
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

}
#pragma endregion DodgeState
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

}
#pragma endregion FallState
#pragma region AttackState
AttackState* AttackState::getInstance()
{
	static AttackState* instance;
	if (instance == nullptr)
		instance = new AttackState();
	return instance;
}

void AttackState::Enter(BaseGameEntity* curState)
{
	curState->SetStateEnum(StateEnum::Attack);
	curState->PlayTime = 0.0f;
	curState->bIsEnd = false;
}

void AttackState::Execute(BaseGameEntity* curState)
{

}

void AttackState::Exit(BaseGameEntity* curState)
{

}
#pragma endregion AttackState
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

}
#pragma endregion HitState
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

}
#pragma endregion DeathState