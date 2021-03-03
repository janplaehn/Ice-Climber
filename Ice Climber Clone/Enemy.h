#pragma once
#include "Component.h"
class Enemy : public Component
{
public:

    virtual void Update() override = 0;
    virtual void Damage() = 0;

    bool _isDead = false;
};

