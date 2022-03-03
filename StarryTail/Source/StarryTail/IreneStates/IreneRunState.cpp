#pragma once

#include "IreneRunState.h"
#include "BaseGameEntity.h"

IreneRunState* IreneRunState::getInstance()
{
    static IreneRunState* instance;
    if (instance == nullptr)
        instance = new IreneRunState();
    return instance;
}

void IreneRunState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Run);
}

// 다른 상태 인클루드 필요
void IreneRunState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneRunState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
