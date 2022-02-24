#pragma once
#include "State.h"

class IreneJumpState : public State
{
public:
    static IreneJumpState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};