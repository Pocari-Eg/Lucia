#pragma once
#include "State.h"

class IreneDashState : public State
{
public:
    static IreneDashState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};