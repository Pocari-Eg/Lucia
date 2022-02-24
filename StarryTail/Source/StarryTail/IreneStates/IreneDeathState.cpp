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
    // Idle ���� ����
    curState->setState(StateEnum::Death);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneDeathState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneDeathState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
