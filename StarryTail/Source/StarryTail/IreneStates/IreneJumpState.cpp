#pragma once

#include "IreneJumpState.h"
#include "BaseGameEntity.h"

IreneJumpState* IreneJumpState::getInstance()
{
    static IreneJumpState* instance;
    if (instance == nullptr)
        instance = new IreneJumpState();
    return instance;
}

void IreneJumpState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Jump);
}

// 다른 상태 인클루드 필요
void IreneJumpState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneJumpState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
