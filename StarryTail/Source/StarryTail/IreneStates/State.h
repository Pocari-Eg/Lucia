#pragma once

class BaseGameEntity;

class State
{
public:
	virtual void Enter(BaseGameEntity*) = 0;
	virtual void Execute(BaseGameEntity*) = 0;
	virtual void Exit(BaseGameEntity*) = 0;
};

