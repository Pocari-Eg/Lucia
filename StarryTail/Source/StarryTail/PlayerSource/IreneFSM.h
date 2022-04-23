// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "PlayerCharacterDataStruct.h"
//#include "../STGameInstance.h"

#include "IreneFSM.generated.h"

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

class IBaseGameEntity;
class IState;

#pragma region StateInterface
UINTERFACE()
class UState : public UInterface
{
	GENERATED_BODY()
};
class IState
{
	GENERATED_BODY()
public:
	virtual void Enter(IBaseGameEntity*) = 0;
	virtual void Execute(IBaseGameEntity*) = 0;
	virtual void Exit(IBaseGameEntity*) = 0;
};

UINTERFACE()
class UBaseGameEntity : public UInterface
{
	GENERATED_BODY()
};
class IBaseGameEntity
{
	GENERATED_BODY()
public:
	float PlayTime;
	bool bIsEnd;
public:
	virtual void Update(const float Value) = 0;
	virtual void ChangeState(IState* NewState) = 0;
	
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
//UCLASS()
class UIdleState final : public IState
{
	//GENERATED_BODY()
public:
	static UIdleState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UDeathState final : public IState
{
public:
	static UDeathState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UDodgeState final : public IState
{
public:
	static UDodgeState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UHitState final : public IState
{
public:
	static UHitState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UBasicAttackState final : public IState
{
public:
	static UBasicAttackState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UActionAttackState final : public IState
{
public:
	static UActionAttackState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UBattleIdleState final : public IState
{
public:
	static UBattleIdleState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class URunState final : public IState
{
public:
	static URunState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class USprintState final : public IState
{
public:
	static USprintState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class USprintEndState final : public IState
{
public:
	static USprintEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UJumpState final : public IState
{
public:
	static UJumpState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class UFallState final : public IState
{
public:
	static UFallState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
class USprintJumpState final : public IState
{
public:
	static USprintJumpState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion State

UCLASS()
class STARRYTAIL_API UIreneFSM final : public UObject, public IBaseGameEntity
{
	GENERATED_BODY()
private:
	IState* StateValue;
	EStateEnum StateEnumValue;
public:
	UIreneFSM(): StateEnumValue(EStateEnum::Idle)
	{
		//StateValue = USTGameInstance::GetIdleInstance();
		
		StateValue->Enter(this);
	}
	virtual void Update(const float Value) override;
	virtual void ChangeState(IState* NewState) override;

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
	void SetState(IState* Value) {
		StateValue = Value;
		if (Value == nullptr)
		{
			//StateValue = USTGameInstance::GetIdleInstance();
			StateEnumValue = EStateEnum::Idle;
		}
	}

	FString GetStateToString() const;
};
