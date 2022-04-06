// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

UENUM(BlueprintType)
enum class StateEnum: uint8
{
	Idle = 0,
	AttackIdle,
	Run,
	Sprint,
	Dodge,
	Jump,
	Fall,
	Attack,
	Hit,
	Death
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

	virtual void SetMaxMoveSpeed(float value) = 0;
	virtual void SetIsInAir(bool value) = 0;
	virtual void SetIsDodge(bool value) = 0;
	virtual void SetIsHit(bool value) = 0;
	virtual void SetIsAttack(bool value) = 0;
	virtual void SetIsDead(bool value) = 0;
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
class AttackIdleState :public State
{
public:
	static AttackIdleState* getInstance();
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
class DodgeState :public State
{
public:
	static DodgeState* getInstance();
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
class AttackState :public State
{
public:
	static AttackState* getInstance();
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
class DeathState :public State
{
public:
	static DeathState* getInstance();
	void Enter(BaseGameEntity* curState);
	void Execute(BaseGameEntity* curState);
	void Exit(BaseGameEntity* curState);
};

#pragma endregion State

class IreneFSM: public BaseGameEntity
{
private:
	State* StateValue;
	StateEnum StateEnumValue;
	//최대 이동 속도 변수: idle, run, sprint
	//공중에 있는지 변수: jump, fall
	//이벤트 상태(시간 후 풀림): dodge, hit, attack
	//종료 상태: dead
	float MaxMoveSpeed;
	bool bIsInAir;
	bool bIsDodge;
	bool bIsHit;
	bool bIsAttack;
	bool bIsDead;

public:
	IreneFSM() : BaseGameEntity(), StateValue(IdleState::getInstance()), StateEnumValue(StateEnum::Idle) { StateValue->Enter(this); };
	void Update(float value);
	void ChangeState(State* newState);

	void SetMaxMoveSpeed(float value) { MaxMoveSpeed = value; };
	void SetIsInAir(bool value) { bIsInAir = value; };
	void SetIsDodge(bool value) { bIsDodge = value; };
	void SetIsHit(bool value) { bIsHit = value; };
	void SetIsAttack(bool value) { bIsAttack = value; };
	void SetIsDead(bool value) { bIsDead = value; };
	void SetStateEnum(StateEnum value) { StateEnumValue = value; };

	StateEnum getState() { return StateEnumValue; };
	void setState(State* val) {
		StateValue = val;
		if (val == nullptr) 
		{
			StateValue = IdleState::getInstance();
			StateEnumValue = StateEnum::Idle;
		}
	};

	FString getStateToString();
	const char* StateEnumToString(StateEnum s);
};
