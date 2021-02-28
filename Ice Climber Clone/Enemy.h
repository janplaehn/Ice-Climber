#pragma once
#include "Component.h"
class Enemy : public Component
{
public:
    Enemy(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

    virtual void Update(float dt) override = 0;
    virtual void Damage() = 0;

    bool _isDead = false;
};

