#pragma once

#include "IreneAttackState.h"
#include "BaseGameEntity.h"

IreneAttackState* IreneAttackState::getInstance()
{
    static IreneAttackState* instance;
    if (instance == nullptr)
        instance = new IreneAttackState();
    return instance;
}

void IreneAttackState::Enter(BaseGameEntity* curState)
{
    // Idle ���� ����
    curState->setState(StateEnum::Attack);
}

// �ٸ� ���� ��Ŭ��� �ʿ�
void IreneAttackState::Execute(BaseGameEntity* curState)
{
    // �̵��ؾ� �ϴ� ������ �ν��Ͻ��� �����´�.
    //curState->ChangeState(GoHomeAndSleepTilRested::getInstance());
}

void IreneAttackState::Exit(BaseGameEntity* curState)
{
    // Idle ���� Ż��
}
