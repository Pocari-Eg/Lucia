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
    // Idle ���� ����
    curState->setState(StateEnum::AttackIdle);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneAttackIdleState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneAttackIdleState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
