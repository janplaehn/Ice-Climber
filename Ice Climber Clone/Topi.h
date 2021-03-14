#pragma once
#include "Enemy.h"
#include "FiniteStateMachine.h"

class AudioSource;
class Animation;
class Sprite;

class Topi : public Enemy, public FiniteStateMachine
{
public:

	Animation* _animation;
	GameObject* _ice;
	Sprite* _deathSprite;
	AudioSource* _deathSource;
	AudioSource* _fallSource;

public:

	virtual void BeginPlay() override;
	virtual void Update() override;
	void ChangeDirection();
	void Damage() override;
};