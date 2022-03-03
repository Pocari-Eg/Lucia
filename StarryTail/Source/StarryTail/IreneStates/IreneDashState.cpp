#pragma once

#include "IreneDashState.h"
#include "BaseGameEntity.h"

IreneDashState* IreneDashState::getInstance()
{
    static IreneDashState* instance;
    if (instance == nullptr)
        instance = new IreneDashState();
    return instance;
}

void IreneDashState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Dash);
}

// 다른 상태 인클루드 필요
void IreneDashState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneDashState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
