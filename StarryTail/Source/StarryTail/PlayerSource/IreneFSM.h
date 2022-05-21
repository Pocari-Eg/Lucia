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
class STARRYTAIL_API UDodgeFireStartState final : public UObject, public IState
{
	GENERATED_BODY()
private:
	FTimerHandle MoveAutoWaitHandle;
public:
	static UDodgeFireStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeFireEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UDodgeFireEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeWaterStartState final : public UObject, public IState
{
	GENERATED_BODY()
private:
	FTimerHandle MoveAutoWaitHandle;
public:
	static UDodgeWaterStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeWaterEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UDodgeWaterEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeThunderStartState final : public UObject, public IState
{
	GENERATED_BODY()
private:
	FTimerHandle MoveAutoWaitHandle;
public:
	static UDodgeThunderStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UDodgeThunderEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static UDodgeThunderEndState* GetInstance();
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
class STARRYTAIL_API UBasicAttack1FireState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack1FireState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack2FireState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack2FireState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack3FireState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack3FireState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack1WaterState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack1WaterState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack2WaterState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack2WaterState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack3WaterState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack3WaterState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack1ThunderState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack1ThunderState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack2ThunderState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack2ThunderState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UBasicAttack3ThunderState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static UBasicAttack3ThunderState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Attack

#pragma region Skill
UCLASS()
class STARRYTAIL_API USkillFireStartState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static USkillFireStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USkillFireEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static USkillFireEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USkillWaterStartState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static USkillWaterStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USkillWaterEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static USkillWaterEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USkillThunderStartState final : public UObject, public IState
{
	GENERATED_BODY()
	float StartShakeTime;
public:
	static USkillThunderStartState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API USkillThunderEndState final : public UObject, public IState
{
	GENERATED_BODY()
public:
	static USkillThunderEndState* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Skill

#pragma region Charge
UCLASS()
class STARRYTAIL_API UCharge1State final : public UObject, public IState
{
	GENERATED_BODY()
private:
	float CurrentTime;
public:
	static UCharge1State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
UCLASS()
class STARRYTAIL_API UCharge2State final : public UObject, public IState
{
	GENERATED_BODY()
private:
	float CurrentTime;
public:
	static UCharge2State* GetInstance();
	virtual void Enter(IBaseGameEntity* CurState) override;
	virtual void Execute(IBaseGameEntity* CurState) override;
	virtual void Exit(IBaseGameEntity* CurState) override;
};
#pragma endregion Charge

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
	FName GetStateToAttackDataTableName() const;

	bool IsIdleState()const;
	bool IsRunState()const;
	bool IsSprintState()const;
	bool IsDodgeState()const;
	bool IsJumpState()const;
	bool IsAttackState()const;
	bool IsSkillState()const;
	bool IsChargeState()const;
	bool IsFormChangeState()const;
	bool IsHitState()const;
	bool IsDeathState()const;

	bool IsFirstAttack()const;

};
