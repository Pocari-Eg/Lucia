#pragma once

#include "IreneWalkState.h"
#include "BaseGameEntity.h"

IreneWalkState* IreneWalkState::getInstance()
{
    static IreneWalkState* instance;
    if (instance == nullptr)
        instance = new IreneWalkState();
    return instance;
}

void IreneWalkState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::Walk);
}

// 다른 상태 인클루드 필요
void IreneWalkState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneWalkState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
