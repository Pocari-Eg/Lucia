// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

enum class StateEnum {
	Idle = 0,
	AttackIdle,
	Walk,
	Run,
	Dash,
	Jump,
	Attack,
	Hit,
	Death
};

class IreneFSM
{
private:
	enum StateEnum StateEnumValue;

public:
	IreneFSM(): StateEnumValue(StateEnum::Idle) { };
	StateEnum getState();
	void setState(StateEnum val);
	const char* StateEnumToString(StateEnum s);
};
