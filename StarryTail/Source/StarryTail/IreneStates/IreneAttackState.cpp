#pragma once

#include "IreneAttackState.h"
#include "BaseGameEntity.h"

IreneAttackState* IreneAttackState::getInstance()
{
    static IreneAttackState* instance;
    if (instance == nullptr)
        instance = new IreneAttackState();
    return instance;
}

void IreneAttackState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Attack);
}

// 다른 상태 인클루드 필요
void IreneAttackState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneAttackState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
