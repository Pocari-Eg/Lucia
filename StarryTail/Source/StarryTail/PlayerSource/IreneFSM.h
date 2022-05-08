// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "IreneFSMInterface.h"
#include "IreneFSM.generated.h"

class AIreneCharacter;

#pragma region State
UCLASS()
class STARRYTAIL_API UIdleState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UIdleState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDeathState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UDeathState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UDodgeState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UHitState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UHitState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttackState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UBasicAttackState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UActionAttackState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UActionAttackState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBattleIdleState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UBattleIdleState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API URunState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static URunState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USprintState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static USprintState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USprintEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static USprintEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UJumpState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UJumpState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UFallState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UFallState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USprintJumpState final : public UObject, public IState
{
	GENERATED_BODY()
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
	UIreneFSM():StateValue(UIdleState::GetInstance()), StateEnumValue(EStateEnum::Idle)
	{
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

	void Init(AIreneCharacter* Value);
	void SetIreneCharacter(AIreneCharacter* Value);
	
	EStateEnum GetState() const { return StateEnumValue; }
	void SetState(IState* Value) {
		StateValue = Value;
		if (Value == nullptr)
		{
			StateValue = UIdleState::GetInstance();
			StateEnumValue = EStateEnum::Idle;
		}
	}

	FString GetStateToString() const;
};
