#pragma once

#include "IreneAttackIdleState.h"
#include "BaseGameEntity.h"

IreneAttackIdleState* IreneAttackIdleState::getInstance()
{
    static IreneAttackIdleState* instance;
    if (instance == nullptr)
        instance = new IreneAttackIdleState();
    return instance;
}

void IreneAttackIdleState::Enter(BaseGameEntity* curState)
{
    // Idle 상태 진입
    curState->setState(StateEnum::AttackIdle);
}

// 다른 상태 인클루드 필요
void IreneAttackIdleState::Execute(BaseGameEntity* curState)
{
    // 이동해야 하는 상태의 인스턴스를 가져온다.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneAttackIdleState::Exit(BaseGameEntity* curState)
{
    // Idle 상태 탈출
}
