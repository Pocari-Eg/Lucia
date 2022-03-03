#pragma once

#include "IreneJumpState.h"
#include "BaseGameEntity.h"

IreneJumpState* IreneJumpState::getInstance()
{
    static IreneJumpState* instance;
    if (instance == nullptr)
        instance = new IreneJumpState();
    return instance;
}

void IreneJumpState::Enter(BaseGameEntity* curState)
{
    // Idle ���� ����
    curState->setState(StateEnum::Jump);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneJumpState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneJumpState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
