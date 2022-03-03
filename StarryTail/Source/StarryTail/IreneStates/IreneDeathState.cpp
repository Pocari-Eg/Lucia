#pragma once

#include "IreneDeathState.h"
#include "BaseGameEntity.h"

IreneDeathState* IreneDeathState::getInstance()
{
    static IreneDeathState* instance;
    if (instance == nullptr)
        instance = new IreneDeathState();
    return instance;
}

void IreneDeathState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Death);
}

// 다른 상태 인클루드 필요
void IreneDeathState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneDeathState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
