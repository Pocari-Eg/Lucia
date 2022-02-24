#pragma once
#include "State.h"

class IreneAttackIdleState : public State
{
public:
    static IreneAttackIdleState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};