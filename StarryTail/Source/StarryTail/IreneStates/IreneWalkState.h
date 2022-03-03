#pragma once
#include "State.h"

class IreneWalkState : public State
{
public:
    static IreneWalkState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};