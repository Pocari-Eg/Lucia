#pragma once

#include "IreneIdleState.h"
#include "BaseGameEntity.h"

IreneIdleState* IreneIdleState::getInstance()
{
    static IreneIdleState* instance;
    if (instance == nullptr)
        instance = new IreneIdleState();
    return instance;
}

void IreneIdleState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Idle);
}

// 다른 상태 인클루드 필요
void IreneIdleState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneIdleState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
