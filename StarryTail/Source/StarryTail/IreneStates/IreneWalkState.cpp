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
    // Idle ���� ����
    curState->setState(StateEnum::Walk);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneWalkState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneWalkState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
