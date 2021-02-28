#pragma once
#include "Component.h"
class HammerTrigger : public Component
{
public:
	HammerTrigger(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Update(float dt) override;

	void OnCollision(class AABBCollider* other);

	class AudioSource* _tileBreakSource;

private:
	std::vector<GameObject*> _triggeredTiles; //Making sure to only break tiles once per update and that it is the closest to the hammer!
	float _timer = 0;
	float _coolDown = 0.2f;
};

