// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../StarryTail.h"

#include "IreneFSMInterface.generated.h"

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
