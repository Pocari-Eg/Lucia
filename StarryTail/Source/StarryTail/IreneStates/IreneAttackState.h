#pragma once
#include "State.h"

class IreneAttackState : public State
{
public:
    static IreneAttackState* getInstance();
    void Enter(BaseGameEntity* curState);
    void Execute(BaseGameEntity* curState);
    void Exit(BaseGameEntity* curState);
};