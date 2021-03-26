#pragma once
#include "Enemy.h"
#include "FiniteStateMachine.h"

class AudioSource;
class Animation;
class Sprite;

class Topi : public Enemy, public FiniteStateMachine
{
public:

	std::shared_ptr<Animation> _animation;
	std::shared_ptr<GameObject> _ice;
	Sprite* _deathSprite;
	std::shared_ptr<AudioSource> _deathSource;
	std::shared_ptr<AudioSource> _fallSource;

public:

	virtual void BeginPlay() override;
	virtual void Update() override;
	void ChangeDirection();
	void Damage() override;

public:
	friend class cereal::access;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Enemy>(this), _animation, _ice, _deathSource, _fallSource);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Topi, "Topi")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Topi, Enemy)