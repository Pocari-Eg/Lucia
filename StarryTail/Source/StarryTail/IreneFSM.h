// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

// 13°³
UENUM(BlueprintType)
enum class StateEnum : uint8
{
	Idle = 0,
	Death,
	Dodge,
	Hit,
	BasicAttack,
	ActionAttack,
	BattleIdle,
	Run,
	Sprint,
	SprintEnd,
	Jump,
	Fall,
	SprintJump
};

class BaseGameEntity;
class State;
class BaseGameEntity;
class IdleState;

#pragma region StateInterface
class State
{
public:
	virtual void Enter(BaseGameEntity*) = 0;
	virtual void Execute(BaseGameEntity*) = 0;
	virtual void Exit(BaseGameEntity*) = 0;
};

class BaseGameEntity
{
public:
	float PlayTime;
	bool bIsEnd;
public:
	BaseGameEntity();
	virtual void Update(float value) = 0;
	virtual void ChangeState(State* newState) = 0;

	virtual void SetStateEnum(StateEnum value) = 0;

	virtual bool CanIdle() = 0;
	virtual bool CanDeath() = 0;
	virtual bool CanDodge() = 0;
	virtual bool CanHit() = 0;
	virtual bool CanBasicAttack() = 0;
	virtual bool CanActionAttack() = 0;
	virtual bool CanBattleIdle() = 0;
	virtual bool CanRun() = 0;
	virtual bool CanSprint() = 0;
	virtual bool CanSprintEnd() = 0;
	virtual bool CanJump() = 0;
	virtual bool CanFall() = 0;
	virtual bool CanSprintJump() = 0;
};
#pragma endregion StateInterface

#pragma region State
class IdleState :public State
{
public:
	static IdleState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class DeathState :public State
{
public:
	static DeathState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class DodgeState :public State
{
public:
	static DodgeState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class HitState :public State
{
public:
	static HitState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class BasicAttackState :public State
{
public:
	static BasicAttackState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class ActionAttackState :public State
{
public:
	static ActionAttackState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class BattleIdleState :public State
{
public:
	static BattleIdleState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class RunState :public State
{
public:
	static RunState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class SprintState :public State
{
public:
	static SprintState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class SprintEndState :public State
{
public:
	static SprintEndState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class JumpState :public State
{
public:
	static JumpState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class FallState :public State
{
public:
	static FallState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
class SprintJumpState :public State
{
public:
	static SprintJumpState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};
#pragma endregion State

class IreneFSM : public BaseGameEntity
{
private:
	State* StateValue;
	StateEnum StateEnumValue;

public:
	IreneFSM() : BaseGameEntity(), StateValue(IdleState::getInstance()), StateEnumValue(StateEnum::Idle) { StateValue->Enter(this); }
	void Update(float value);
	void ChangeState(State* newState);

	bool CanIdle();
	bool CanDeath();
	bool CanDodge();
	bool CanHit();
	bool CanBasicAttack();
	bool CanActionAttack();
	bool CanBattleIdle();
	bool CanRun();
	bool CanSprint();
	bool CanSprintEnd();
	bool CanJump();
	bool CanFall();
	bool CanSprintJump();

	void SetStateEnum(StateEnum value) { StateEnumValue = value; }

	StateEnum getState() { return StateEnumValue; }
	void setState(State* val) {
		StateValue = val;
		if (val == nullptr)
		{
			StateValue = IdleState::getInstance();
			StateEnumValue = StateEnum::Idle;
		}
	}

	FString getStateToString();
};
