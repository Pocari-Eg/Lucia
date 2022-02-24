#pragma once
#include "State.h"

class IreneDeathState : public State
{
public:
    static IreneDeathState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};