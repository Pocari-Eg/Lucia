#pragma once
#include "State.h"

class IreneRunState : public State
{
public:
    static IreneRunState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};