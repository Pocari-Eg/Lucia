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
    // Idle ���� ����
    curState->setState(StateEnum::Idle);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneIdleState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneIdleState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
