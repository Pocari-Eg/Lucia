#pragma once
#include "State.h"

class IreneHitState : public State
{
public:
    static IreneHitState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};