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
    // Idle ���� ����
    curState->setState(StateEnum::Hit);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneHitState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneHitState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
