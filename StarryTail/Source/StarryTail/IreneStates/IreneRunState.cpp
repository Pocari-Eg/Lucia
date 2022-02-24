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
    // Idle ���� ����
    curState->setState(StateEnum::Run);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneRunState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneRunState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
