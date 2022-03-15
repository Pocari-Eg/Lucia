// Fill out your copyright notice in the Description page of Project Settings.

#include "IreneFSM.h"

StateEnum IreneFSM::getState()
{
	return StateEnumValue;
}

void IreneFSM::setState(StateEnum val)
{
	StateEnumValue = val;
}

const char* IreneFSM::StateEnumToString(StateEnum s)
{
    switch(s)
    {
    case StateEnum::Idle: return "Idle";
    case StateEnum::AttackIdle: return "AttackIdle";
    case StateEnum::Walk: return "Walk";
    case StateEnum::Run: return "Run";
    case StateEnum::Dash: return "Dash";
    case StateEnum::Jump: return "Jump";
    case StateEnum::Attack: return "Attack";
    case StateEnum::Hit: return "Hit";
    case StateEnum::Death: return "Death";
    default: return "Error StateEnumToString";
    }
}