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
    // Idle ���� ����
    curState->setState(StateEnum::Dash);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneDashState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneDashState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
