#pragma once
#include "Component.h"
class HammerTrigger : public Component
{
public:

	virtual void Update() override;

	void OnCollision(class AABBCollider* other, Vector2D normal) override;

	class AudioSource* _tileBreakSource;

private:
	std::vector<GameObject*> _triggeredTiles; //Making sure to only break tiles once per update and that it is the closest to the hammer!
	float _timer = 0;
	float _coolDown = 0.3f;
};

