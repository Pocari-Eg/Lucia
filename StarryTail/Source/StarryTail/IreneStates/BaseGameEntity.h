#pragma once

enum class StateEnum {
    Idle,
    AttackIdle,
    Walk,
    Run,
    Dash,
    Jump,
    Attack,
    Hit,
    Death
};

class State;

class BaseGameEntity
{
public:
    BaseGameEntity() {}
    virtual void Update() = 0;
    virtual void ChangeState(State* newState) = 0;
    virtual StateEnum getState() = 0;
    virtual void setState(StateEnum val) = 0;
};
