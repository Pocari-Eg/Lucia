#pragma once
#include "State.h"

class IreneIdleState : public State
{
public:
    static IreneIdleState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};