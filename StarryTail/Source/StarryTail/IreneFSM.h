// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "./IreneStates/BaseGameEntity.h"
#include "./IreneStates/State.h"
#include "./IreneStates/IreneIdleState.h"
#include "./IreneStates/IreneAttackIdleState.h"
#include "./IreneStates/IreneWalkState.h"
#include "./IreneStates/IreneRunState.h"
#include "./IreneStates/IreneDashState.h"
#include "./IreneStates/IreneJumpState.h"
#include "./IreneStates/IreneAttackState.h"
#include "./IreneStates/IreneHitState.h"
#include "./IreneStates/IreneDeathState.h"

class State;

class IreneFSM : public BaseGameEntity
{
public:

protected:

private:
	State* StateValue;
	StateEnum StateEnumValue;

public:
	IreneFSM() : BaseGameEntity(), StateValue(IreneIdleState::getInstance()), StateEnumValue(StateEnum::Idle) { StateValue->Enter(this); }
	void Update();
	void ChangeState(State* newState);
	StateEnum getState();
	void setState(StateEnum val);
	const char* StateEnumToString(StateEnum s);

protected:

private:

};
