// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "IreneFSMInterface.h"
#include "IreneFSM.generated.h"

class AIreneCharacter;

#pragma region State

#pragma region Idle
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
class STARRYTAIL_API UBattleIdleState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UBattleIdleState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Idle

#pragma region Run
UCLASS()
class STARRYTAIL_API URunLoopState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static URunLoopState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API URunEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static URunEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Run

#pragma region Sprint
UCLASS()
class STARRYTAIL_API USprintLoopState final : public UObject, public IState
{
	GENERATED_BODY()
private:
	TArray<uint8> ChangeMoveKey;
public:
	static USprintLoopState* GetInstance();
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
#pragma endregion Sprint

#pragma region Dodge
UCLASS()
class STARRYTAIL_API UDodgeStartState final : public UObject, public IState
{
	GENERATED_BODY()
private:
	EStateEnum BeforeStateEnum;
public:
	static UDodgeStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UDodgeEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Dodge

#pragma region Jump
UCLASS()
class STARRYTAIL_API UJumpStartState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UJumpStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UJumpLoopState final : public UObject, public IState
{
	GENERATED_BODY()
private:
	float CurrentTime;
public:
	static UJumpLoopState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UJumpEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UJumpEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Jump

#pragma region Attack
UCLASS()
class STARRYTAIL_API UBasicAttack1State final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static UBasicAttack1State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
UCLASS()
class STARRYTAIL_API UBasicAttack2State final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static UBasicAttack2State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
UCLASS()
class STARRYTAIL_API UBasicAttack3State final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static UBasicAttack3State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
#pragma endregion Attack

#pragma region Skill
UCLASS()
class STARRYTAIL_API USwordSkill1 final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static USwordSkill1* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
UCLASS()
class STARRYTAIL_API USwordSkill2 final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static USwordSkill2* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
UCLASS()
class STARRYTAIL_API USpiritSkill final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static USpiritSkill* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
#pragma endregion Skill

#pragma region UltimateAttack
UCLASS()
class STARRYTAIL_API UUltimateAttack final : public UObject, public IState
{
	GENERATED_BODY()
	float EndTime;
	float StartShakeTime;
public:
	static UUltimateAttack* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
	void EndTimeExit(IBaseGameEntity* CurState);
};
#pragma endregion UltimateAttack

#pragma region FormChange
UCLASS()
class STARRYTAIL_API UFormChangeState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UFormChangeState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion FormChange

#pragma region Hit
UCLASS()
class STARRYTAIL_API UHit1State final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UHit1State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UHit2State final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UHit2State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UKnockBackState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UKnockBackState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Hit

#pragma region Death
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
#pragma endregion Death

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
	virtual void ThrowState(IState* NewState) override;

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

	bool IsIdleState()const;
	bool IsRunState()const;
	bool IsSprintState()const;
	bool IsDodgeState()const;
	bool IsJumpState()const;
	bool IsAttackState()const;
	bool IsSkillState()const;
	UFUNCTION(BlueprintCallable)
	bool IsUltimateAttackState()const;
	bool IsFormChangeState()const;
	bool IsHitState()const;
	bool IsDeathState()const;

	bool IsFirstAttack()const;
	bool IsSecondAttack() const;
	bool IsThirdAttack() const;

	bool IsKnockBackState()const;
};
