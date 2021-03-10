#pragma once
#include "Component.h"

class Enemy : public Component
{
public:

    virtual void Damage() = 0;

protected:

    bool _isDead = false;
};

