#pragma once

#include "IreneHitState.h"
#include "BaseGameEntity.h"

IreneHitState* IreneHitState::getInstance()
{
    static IreneHitState* instance;
    if (instance == nullptr)
        instance = new IreneHitState();
    return instance;
}

void IreneHitState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Hit);
}

// 다른 상태 인클루드 필요
void IreneHitState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneHitState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
