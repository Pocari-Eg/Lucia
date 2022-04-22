// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "PlayerCharacterDataStruct.h"

// 13°³
UENUM(BlueprintType)
enum class EStateEnum : uint8
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

class FBaseGameEntity;
class FState;
class FIdleState;

#pragma region StateInterface
class FState
{
public:
	virtual ~FState() = default;
	virtual void Enter(FBaseGameEntity*) = 0;
	virtual void Execute(FBaseGameEntity*) = 0;
	virtual void Exit(FBaseGameEntity*) = 0;
};

class FBaseGameEntity
{
public:
	virtual ~FBaseGameEntity() = default;
	float PlayTime;
	bool bIsEnd;
	FPlayerCharacterDataStruct* CharacterDataStruct;
public:
	FBaseGameEntity(){};
	FBaseGameEntity(FPlayerCharacterDataStruct* Value);
	virtual void Update(const float Value) = 0;
	virtual void ChangeState(FState* NewState) = 0;
	
	virtual void SetStateEnum(EStateEnum Value) = 0;

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
class FIdleState final :public FState
{
	float BeforeTime = 0.0f;
	float HpTime = 0.0f;
public:
	static FIdleState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FDeathState final :public FState
{
public:
	static FDeathState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FDodgeState final :public FState
{
public:
	static FDodgeState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FHitState final :public FState
{
public:
	static FHitState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FBasicAttackState final :public FState
{
public:
	static FBasicAttackState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FActionAttackState final :public FState
{
public:
	static FActionAttackState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FBattleIdleState final :public FState
{
public:
	static FBattleIdleState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FRunState final :public FState
{
public:
	static FRunState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FSprintState final :public FState
{
public:
	static FSprintState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FSprintEndState final :public FState
{
public:
	static FSprintEndState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FJumpState final :public FState
{
public:
	static FJumpState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FFallState final :public FState
{
public:
	static FFallState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
class FSprintJumpState final :public FState
{
public:
	static FSprintJumpState* GetInstance();
	virtual void Enter(FBaseGameEntity* CurState) override;
	virtual void Execute(FBaseGameEntity* CurState) override;
	virtual void Exit(FBaseGameEntity* CurState) override;
};
#pragma endregion State

class FIreneFSM final : public FBaseGameEntity
{
private:
	FState* StateValue;
	EStateEnum StateEnumValue;
	
public:
	FIreneFSM():StateValue(FIdleState::GetInstance()), StateEnumValue(EStateEnum::Idle) { StateValue->Enter(this); }
	FIreneFSM(FPlayerCharacterDataStruct* Value) : FBaseGameEntity(Value), StateValue(FIdleState::GetInstance()), StateEnumValue(EStateEnum::Idle) { StateValue->Enter(this); }
	virtual void Update(const float Value) override;
	virtual void ChangeState(FState* NewState) override;

	virtual bool CanIdle() override;
	virtual bool CanDeath() override;
	virtual bool CanDodge() override;
	virtual bool CanHit() override;
	virtual bool CanBasicAttack() override;
	virtual bool CanActionAttack() override;
	virtual bool CanBattleIdle() override;
	virtual bool CanRun() override;
	virtual bool CanSprint() override;
	virtual bool CanSprintEnd() override;
	virtual bool CanJump() override;
	virtual bool CanFall() override;
	virtual bool CanSprintJump() override;

	virtual void SetStateEnum(const EStateEnum Value) override { StateEnumValue = Value; }

	EStateEnum GetState() const { return StateEnumValue; }
	void SetState(FState* Value) {
		StateValue = Value;
		if (Value == nullptr)
		{
			StateValue = FIdleState::GetInstance();
			StateEnumValue = EStateEnum::Idle;
		}
	}

	FString GetStateToString() const;
};
